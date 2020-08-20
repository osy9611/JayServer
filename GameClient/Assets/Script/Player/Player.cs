using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private bool isFirst;
    public bool isPlayer = false;
    private bool isMove = false;
    public float Speed = 5;
    public Vector3 dir;
    public string Name;

    public Vector3 ServerPos;
    public Vector3 ServerDir;
    public float ServerRot;

    private Animator Ani;
    // Start is called before the first frame update
    void Start()
    {
        Ani = GetComponent<Animator>();
        if(isPlayer)
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

        ServerPos = new Vector3(ServerPos.x + ServerDir.x * Time.deltaTime * Speed * NetWork.instance.Latency, ServerPos.y, ServerPos.z + ServerDir.z * Time.deltaTime * Speed * NetWork.instance.Latency);
        transform.position = Vector3.Lerp(transform.position, ServerPos, Time.deltaTime * Speed);

        if(ServerDir == Vector3.zero)
        {
            Ani.SetBool("Walk", false);
        }
        else
        {
            Ani.SetBool("Walk", true);
        }
    }

    void Move()
    {
        dir.x = Input.GetAxisRaw("Horizontal");
        dir.z = Input.GetAxisRaw("Vertical");

        if(Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.S)||
            Input.GetKeyDown(KeyCode.A)|| Input.GetKeyDown(KeyCode.D))
        {
            Write();
            //ServerPos = new Vector3(ServerPos.x + ServerDir.x * Time.deltaTime * Speed * NetWork.instance.Latency, ServerPos.y, ServerPos.z + ServerDir.z * Time.deltaTime * Speed * NetWork.instance.Latency);
        }

        if (Input.GetKeyUp(KeyCode.W) || Input.GetKeyUp(KeyCode.S) ||
            Input.GetKeyUp(KeyCode.A) || Input.GetKeyUp(KeyCode.D))
        {
            Write();
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
        os.Write(this.transform.eulerAngles.y);

        NetWork.instance.Send(os);
    }

}
