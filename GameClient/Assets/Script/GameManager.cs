using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
[System.Serializable]
public struct CharactorData
{
    public string Name;
    public int Level;
    public int Class;
}

public class GameManager : MonoBehaviour
{
    public static GameManager instance;
    public string UserName;
    [SerializeField]
    public List<CharactorData> charactorData = new List<CharactorData>();

    bool robbyOn = false;
    CharactorData dummy;
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

    private void Update()
    {
        if (robbyOn)
        {
            robbyOn = false;
           
        }
    }

    public void StoreCharactorData(InputMemoryStream io)
    {
        short _userCount = 0;
        io.Read(ref _userCount);
        Debug.Log(_userCount);
        if (_userCount > 0)
        {
            for (int i = 0; i < _userCount; ++i)
            {
                string _name = "";
                short _level = 0;
                short _class = 0;
                io.Read(ref _name);
                io.Read(ref _level);
                io.Read(ref _class);
               
                dummy.Name = _name;
                dummy.Level = _level;
                dummy.Class = _class;
                charactorData.Add(dummy);
            }
        }     
    }


}
