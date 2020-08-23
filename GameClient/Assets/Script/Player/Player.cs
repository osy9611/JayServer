using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public Camera mainCamera;
    public Vector3 targetPos;
    public Vector3 storeVector;
    public GameObject a;
    private bool isFirst;
    public bool isPlayer = false;
    private bool isMove = false;
    public float Speed = 5;
    public Vector3 dir;
    public float rot;
    float prevRot;
    float SendTimeStamp = 0.0f;
    public string Name;

    public float mouseX = 0.0f;
    public float mouserWheel = 0.5f;
    public Vector3 ServerPos;
    public Vector3 ServerDir;
    public float ServerRot;

    public Animator Ani;
    // Start is called before the first frame update
    void Start()
    {
        //mainCamera = GameObject.Find("Main Camera").GetComponent<Camera>();
        if (isPlayer)
        {
            PlayerManager.instance.SetPlayer(this);
            PlayerManager.instance.playerName = Name;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (isPlayer)
            Move();
      
        Vector3 lookDir = Vector3.Slerp(a.transform.forward, ServerDir.normalized, Time.deltaTime * 5);
        lookDir.Normalize();

        float angle = Mathf.Acos(Vector3.Dot(Vector3.forward, lookDir)) * Mathf.Rad2Deg;
        
        if (ServerDir == Vector3.zero)
        {
            Ani.SetBool("Walk", false);
        }
        else
        {
            Ani.SetBool("Walk", true);
            ServerPos = new Vector3(ServerPos.x + ServerDir.x * Time.deltaTime * Speed * NetWork.instance.Latency, ServerPos.y, ServerPos.z + ServerDir.z * Time.deltaTime * Speed * NetWork.instance.Latency);
            a.transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);
            transform.position = Vector3.Lerp(transform.position, ServerPos, Time.deltaTime * Speed);
        }
    }

    public bool mouseSend;
    void Move()
    {
        if(Input.GetMouseButton(0))
        {
            Ray ray = mainCamera.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if(Physics.Raycast(ray,out hit,10000f))
            {
                targetPos = new Vector3(hit.point.x, 0, hit.point.z);
            }
        }
        else
        {
            targetPos = Vector3.zero;
            if(storeVector!=Vector3.zero)
            {
                dir = Vector3.zero;
                Write();
                storeVector = Vector3.zero;
            }
        }

        Vector3 dirToTarget = targetPos - transform.position;
        dir = new Vector3((float)(Math.Truncate(dirToTarget.normalized.x * 10) / 10), 0, (float)(Math.Truncate(dirToTarget.normalized.z * 10) / 10));

        if (SendTimeStamp >= 0.2f)
        {
            if (targetPos != Vector3.zero)
            {
                if (storeVector != dir)
                {
                    storeVector = dir;
                    Write();
                }
                else
                {
                    SendTimeStamp = 0;
                }
            }
        }
        else
        {
            SendTimeStamp += Time.deltaTime;
        }
     
    }

    void CheckSameRot()
    {
        if (prevRot != mouseX)
        {
            Write();
            prevRot = mouseX;
        }
    }

    public void SetName(string _name)
    {
        Name = _name;
        PlayerManager.instance.SetPlayer(this);
    }

    public void SetPos(Vector3 _pos, Vector3 _dir, float _rot)
    {
        //isMove = false;
        ServerPos = _pos;
        ServerDir = _dir;
        ServerRot = _rot;

        //isMove = true;
    }

    public void Write()
    {
        OutputMemoryStream os = new OutputMemoryStream();
        os.Write((short)Defines.USER_DATA);
        os.Write(this.Name);
        os.Write(this.transform.position);
        os.Write(dir);
        //os.Write(this.transform.eulerAngles.y);
        os.Write(rot);
        NetWork.instance.Send(os);
    }

}
