using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
public enum PlayerState
{
    Idle,
    Move,
    Attack
}

public class PlayerActor : MonoBehaviour
{
    //플레이어 이름
    public string Name;
    public Transform tr;
    PlayerState PT;
    private GameObject playerObject;
    public Animator Ani;
    private Camera mainCamera;

    //마우스 위치 값
    public Vector3 targetPos;
    //이전 방향을 저장
    public Vector3 storeVector;
    //방향 값
    public Vector3 dir;
    //마우스가 이동할때 0.2초마다 확인시킬 값
    float sendTimeStamp;

    //서버에서 계산된 위치,방향값
    public Vector3 serverPos;
    public Vector3 serverDir;
    
    public void SetObject(string _name,GameObject _obj,Camera _camera)
    {
        Name = _name;
        playerObject = _obj;
        Ani = _obj.GetComponent<Animator>();
        mainCamera = _camera;
    }

    void GetDir()
    {
        Ray ray = mainCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, 10000f))
        {

            targetPos = new Vector3(hit.point.x, 0, hit.point.z);
        }
        Vector3 dirToTarget = targetPos - tr.position;
        dir = new Vector3((float)(Math.Truncate(dirToTarget.normalized.x * 10) / 10), 0, (float)(Math.Truncate(dirToTarget.normalized.z * 10) / 10));

    }

    public void CalcDir(PlayerState _PT)
    {
        PT = _PT;
        GetDir();
        if(PT != PlayerState.Attack)
        {
            CheckSendTime();
        }
        else
        {
            CheckSend();
        }
    }

    public void ResetDir(PlayerState _PT)
    {
        PT = _PT;
        targetPos = Vector3.zero;
        if(storeVector != Vector3.zero)
        {
            dir = Vector3.zero;
            Write(PlayerState.Idle);
            storeVector = Vector3.zero;
        }
    }

    //0.1 초 마다 방향값이 바뀐다면 서버로 보내준다
    void CheckSendTime()
    {
        if (sendTimeStamp >= 0.1f)
        {
            if (targetPos != Vector3.zero)
            {
                if (storeVector != dir)
                {
                    storeVector = dir;
                    Write(PT);
                }
                else
                {
                    sendTimeStamp = 0;
                }
            }
        }
        else
        {
            sendTimeStamp += Time.deltaTime;
        }
    }
    //애니메이션이 끝났을때 보냄
    void CheckSend()
    {
        if (Ani.GetCurrentAnimatorStateInfo(0).IsName("arthur_attack_01") &&
                 Ani.GetCurrentAnimatorStateInfo(0).normalizedTime >= 0.99f)
        {
            if (targetPos != Vector3.zero)
            {
                if (storeVector != dir)
                {
                    storeVector = dir;
                    Write(PT);
                }
            }
        }
    }
    
    public void SimulatonMove(float _speed,PlayerState _PT)
    {
        Vector3 lookDir = Vector3.Slerp(playerObject.transform.forward, serverDir.normalized, Time.deltaTime * 5);
        lookDir.Normalize();

        if(serverDir == Vector3.zero || _PT == PlayerState.Idle)
        {
            Ani.SetBool("Walk", false);
        }
        else
        {
            Ani.SetBool("Walk", true);
            //서버에서 들어오는 딜레이를 추가 계산하여 방향을 예측
            serverPos = new Vector3(serverPos.x + serverDir.x * Time.deltaTime * _speed * NetWork.instance.Latency, serverPos.y, serverPos.z + serverDir.z * Time.deltaTime * _speed * NetWork.instance.Latency);
            tr.position = Vector3.Lerp(tr.position, serverPos, Time.deltaTime * _speed);
            playerObject.transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);

        }

    }

    public void AttackOn()
    {
        Ani.SetBool("Attack",true);
    }

    public void AttackOff()
    {
        Ani.SetBool("Attack", false);
    }

    public void SendAttack(PlayerState _PT)
    {
        PT = _PT;
        GetDir();
        if (_PT == PlayerState.Attack)
        {
            Write(PlayerState.Attack);
        }
        else
        {
            if (serverDir != Vector3.zero)
            {
                Write(PlayerState.Idle);
            }
            else
            {
                Write(PlayerState.Idle);
            }
        }
    }

    public void Write(PlayerState _PT)
    {
        OutputMemoryStream os = new OutputMemoryStream();
        os.Write((short)Defines.USER_DATA);
        os.Write(this.Name);
        os.Write(tr.position);
        os.Write(dir);
        os.Write((short)_PT);
       
        NetWork.instance.Send(os);
    }
}
