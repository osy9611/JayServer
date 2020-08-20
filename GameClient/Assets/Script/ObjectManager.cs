using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//오브젝트를 생성하고 관리해주는 함수
public class ObjectManager : MonoBehaviour
{
    public static ObjectManager instance;

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(this.gameObject);
        }
    }

    public void SetObject(InputMemoryStream inInputStream)
    {
        short Count = 0;
        
        inInputStream.Read(ref Count);
        if (Count != 0)
        {
            PlayerSet(inInputStream, Count);
        }
        inInputStream.Read(ref Count);
        MonsterSet(inInputStream, Count);
    }

    private void PlayerSet(InputMemoryStream inInputStream,short Count)
    {
        for(int i=0;i<Count;++i)
        {
            string name ="";
            inInputStream.Read(ref name);
            Vector3 _pos = Vector3.zero;
            inInputStream.Read(ref _pos);
            Vector3 _dir = Vector3.zero;
            inInputStream.Read(ref _dir);
            float _rot = 0;
            inInputStream.Read(ref _rot);
            PlayerManager.instance.SearchPlayer(name, _pos, _dir,_rot);
        }
    }

    private void MonsterSet(InputMemoryStream inInputStream,short Count)
    {
        for (int i = 0; i < Count; ++i)
        {
            int _id = 0;
            Vector3 _pos = new Vector3();
            Vector3 _dir = new Vector3();
            inInputStream.Read(ref _id);
            inInputStream.Read(ref _pos);
            inInputStream.Read(ref _dir);
            MonsterManager.instance.SearchMonster(_id, _pos, _dir);
        }
    }
}
