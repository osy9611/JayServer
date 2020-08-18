using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public bool isPlayer = false;
    private bool isMove = false;
    public float Speed = 5;
    public Vector3 dir;
    public string Name;

    public Vector3 ServerPos;
    public float ServerRot;
    // Start is called before the first frame update
    void Start()
    {
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
        else
        {
            if (isMove)
            {
                transform.position = Vector3.Lerp(transform.position, ServerPos, Time.deltaTime * Speed);
            }
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
        }

        if (Input.GetKeyUp(KeyCode.W) || Input.GetKeyUp(KeyCode.S) ||
            Input.GetKeyUp(KeyCode.A) || Input.GetKeyUp(KeyCode.D))
        {
            Write();
        }

        transform.Translate(dir.normalized * Time.deltaTime * Speed);
    }

    public void SetName(string _name)
    {
        Name = _name;
        PlayerManager.instance.SetPlayer(this);
    }

    public void SetPos(Vector3 _pos, float _rot)
    {
        isMove = false;
        ServerPos = _pos;
        ServerRot = _rot;
        isMove = true;
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
