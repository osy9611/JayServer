using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    public int id = 0;
    bool isMove = false;
    public Vector3 ServerPos;
    public Vector3 ServerDir;
    // Update is called once per frame
    void Update()
    {
        if(isMove)
        {
            transform.position = Vector3.Lerp(transform.position, ServerPos, Time.deltaTime * 2);
            transform.rotation = Quaternion.LookRotation(ServerDir);
        }
    }

    public void SetId(int _id)
    {
        id = _id;
        MonsterManager.instance.SetMonster(this);
    }
    public int GetId()
    {
        return id;
    }

    public void SetPos(Vector3 _pos,Vector3 _dir)
    {
        isMove = false;
        ServerPos = _pos;
        ServerDir = _dir;
        isMove = true;
    }
}
