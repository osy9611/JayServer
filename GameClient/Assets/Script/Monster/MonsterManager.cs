using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterManager : MonoBehaviour
{
    public static MonsterManager instance;

    public Dictionary<int, Monster> Monsters = new Dictionary<int, Monster>();
    public GameObject Monster;

    private bool IsSet=false;
    public int _setId;
    private Vector3 _setPos;
    private Vector3 _setDir;
    private float _setHp;

    public List<int> collisionCheckList = new List<int>();

    private object lockObject = new object();
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

    private void Update()
    {
        lock(lockObject)
        {
            if (IsSet)
            {
                GameObject obj = Instantiate(this.Monster, _setPos, Quaternion.identity);
                obj.GetComponent<Monster>().SetId(_setId, _setHp);
                IsSet = false;
            }
        }
     
    }
    
    public void SetMonster(Monster _monster)
    {
        Monsters.Add(_monster.GetId(), _monster);
    }

    public void SearchMonster(int _id,Vector3 _pos,Vector3 _dir,float _hp)
    {
        lock(lockObject)
        {
            if (Monsters.ContainsKey(_id))
            {
                Monsters[_id].SetPos(_pos, _dir, _hp);
            }
            else
            {
                CreateMonster(_id, _pos, _dir, _hp);
            }
        }
     
    }

    public void CreateMonster(int _id, Vector3 _pos, Vector3 _dir, float _hp)
    {
        _setId = _id;
        _setPos = _pos;
        _setDir = _dir;
        _setHp = _hp;
        IsSet = true;
    }

    public void SetCollisionCheck(int _id)
    {
        if(!collisionCheckList.Contains(_id))
        {
            collisionCheckList.Add(_id);
        }
        
    }

    public void Write(string name)
    {
        if(collisionCheckList.Count != 0)
        {
            OutputMemoryStream os = new OutputMemoryStream();
            os.Write((short)Defines.CHECK_MONSTERS);
            os.Write(name);
            os.Write((short)collisionCheckList.Count);
            for (int i = 0; i < collisionCheckList.Count; ++i)
            {
                os.Write((short)collisionCheckList[i]);
            }

            NetWork.instance.Send(os);

            collisionCheckList.Clear();
        }
      
    }
}
