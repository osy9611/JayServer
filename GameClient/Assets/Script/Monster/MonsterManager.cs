using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterManager : MonoBehaviour
{
    public static MonsterManager instance;

    public Dictionary<int, Monster> Monsters = new Dictionary<int, Monster>();

    private void Awake()
    {
        if(instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(this.gameObject);
        }
    }

    public void SetMonster(Monster _monster)
    {
        Monsters.Add(_monster.GetId(), _monster);
    }

    public void SearchMonster(int _id,Vector3 _pos)
    {
        Monsters[_id].SetPos(_pos);
    }
}
