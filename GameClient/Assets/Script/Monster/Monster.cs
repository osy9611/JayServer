using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    public int id = 0;
    public float Hp = 0;
    bool isMove = false;
    public Vector3 ServerPos;
    public Vector3 ServerDir;

    public bool isHit;
    // Update is called once per frame
    void Update()
    {
        if(isMove)
        {
            transform.position = Vector3.Lerp(transform.position, ServerPos, Time.deltaTime * 2);
            transform.rotation = Quaternion.LookRotation(ServerDir);
            if(Hp==0)
            {
                this.gameObject.SetActive(false);
            }
        }
    }

    public void SetId(int _id,float _hp)
    {
        id = _id;
        Hp = _hp;
        MonsterManager.instance.SetMonster(this);
    }
    public int GetId()
    {
        return id;
    }

    public void SetPos(Vector3 _pos,Vector3 _dir,float _hp)
    {
        isMove = false;
        ServerPos = _pos;
        ServerDir = _dir;
        Hp = _hp;
        isMove = true;
        isHit = false;
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Wapon" && !isHit)
        {
            Player player = PlayerManager.instance.CheckUser(other.gameObject.transform.root.name);
            if(player !=null)
            {
                if (player.isPlayer)
                {
                    if (player.PT == PlayerState.Attack)
                    {
                        MonsterManager.instance.SetCollisionCheck(id);
                        isHit = true;
                    }
                }
            }
        }
    }
}
