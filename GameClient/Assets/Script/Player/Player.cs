using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player :MonoBehaviour
{ 
    public string Name;
    public PlayerState PT;
    public bool isPlayer = false;
    //자식 관련 데이터들
    public GameObject playerObject;
    //플레이어 속도
    public float speed;

    //메인 카메라
    public Camera mainCamera;

    PlayerCommand CalcDir,ResetDir,command,Attack;
    public PlayerActor playerActor;

    [HideInInspector]
    public bool updateOK;

    private void Awake()
    {
        playerActor = this.gameObject.AddComponent<PlayerActor>();
        playerActor.SetObject(Name,playerObject,mainCamera);
        playerActor.tr = gameObject.transform;
        SetCommand();
    }

    private void Start()
    {
        if (isPlayer)
        {
            PlayerManager.instance.SetPlayer(this);
            PlayerManager.instance.playerName = Name;
            this.gameObject.name = Name;
        }
    }

    void SetCommand()
    {
        CalcDir = new CalcDir();
        ResetDir = new ResetDir();
        Attack = new Attack();
    }

    private void Update()
    {
        playerActor.SimulatonMove(speed, PT);

        if (PT == PlayerState.Attack)
        {
            playerActor.AttackOn();
        }
        else
        {
            playerActor.AttackOff();
        }

        if (isPlayer)
        {
            InputCheck();
        }

        if(!PlayerManager.instance.CheckUserList(Name) && Name !="")
        {
            Destroy(this.gameObject);
        }
    }

  

    void InputCheck()
    {
        if (Input.GetMouseButton(1))
        {
            CalcDir.Execute(playerActor, PlayerState.Move);
        }
        else if (Input.GetMouseButtonUp(1))
        {
            ResetDir.Execute(playerActor, PlayerState.Idle);
        }
        else if (Input.GetMouseButtonDown(0))
        {
            Attack.Execute(playerActor, PlayerState.Attack);
        }
        else if (Input.GetMouseButton(0))
        {
            CalcDir.Execute(playerActor, PlayerState.Attack);
        }
        else if (Input.GetMouseButtonUp(0))
        {
            Attack.Execute(playerActor, PlayerState.Idle);
        }
        else if(Input.GetMouseButton(1) && Input.GetMouseButtonDown(0))
        {
            Attack.Execute(playerActor, PlayerState.Attack);
        }
    }

    public void SetName(string _name)
    {
        Name = _name;
        gameObject.name = _name;
        PlayerManager.instance.SetPlayer(this);
    }

    public void SetPos(Vector3 _pos, Vector3 _dir,short _playerState)
    {
        playerActor.serverPos = _pos;
        playerActor.serverDir = _dir;
        PT = (PlayerState)_playerState;
    }
}
