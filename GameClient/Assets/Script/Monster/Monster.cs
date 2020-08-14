using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    public int id;
    bool isMove = false;
    public Vector3 ServerPos;

    // Start is called before the first frame update
    void Start()
    {
        MonsterManager.instance.SetMonster(this);
    }

    // Update is called once per frame
    void Update()
    {
        if(isMove)
        {
            transform.position = Vector3.Lerp(transform.position, ServerPos, Time.deltaTime);
        }
    }

    public int GetId()
    {
        return id;
    }

    public void SetPos(Vector3 _pos)
    {
        isMove = false;
        ServerPos = _pos;
        isMove = true;
    }
}
