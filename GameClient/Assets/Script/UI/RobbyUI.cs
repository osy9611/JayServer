using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class RobbyUI : MonoBehaviour
{ 
    //캐릭터 버튼 리스트
    [SerializeField]
    public List<CharactorUIData> charactorList = new List<CharactorUIData>();
    //캐릭터 리스트
    public List<GameObject> Charactors = new List<GameObject>();
    private List<Animator> CharactorsAni = new List<Animator>();

    public GameObject CharactorSelectUI;
    public GameObject CharactorCreateUI;
    //게임 시작
    bool inGameOn = false;

    //캐릭터 생성 관련
    public InputField CreateNameField;
    private string CreateName;
    int _charactorCnt;
    int ClassNum;

    private void Awake()
    {
        for(int i=0;i<Charactors.Count;++i)
        {
            Animator ani = Charactors[i].GetComponent<Animator>();
            CharactorsAni.Add(ani);
        }

        SetChractorList();
    }

    private void Update()
    {
        if (inGameOn)
        {
            inGameOn = false;
            SceneManager.LoadScene("Demo"); 
        }
    }

    public void SetChractorList()
    {
        if(GameManager.instance.charactorData.Count >0)
        {
            _charactorCnt = GameManager.instance.charactorData.Count;
            for (int i = 0; i < GameManager.instance.charactorData.Count; ++i)
            {
                charactorList[i].SetText(GameManager.instance.charactorData[i].Name, GameManager.instance.charactorData[i].Level, GameManager.instance.charactorData[i].Class);
                charactorList[i].gameObject.SetActive(true);
            }
            GameManager.instance.charactorData.Clear();
        }
    }

    public void SetCharactorList(string _name,short _classNum)
    {
        charactorList[_charactorCnt].SetText(_name, 1, _classNum);
        charactorList[_charactorCnt].gameObject.SetActive(true);
    }

    public bool isShow(int classNum)
    {
        if(Charactors[classNum].activeSelf)
        {
            return true;
        }

        return false;
    }

    public void CharactorOn(int _classNum)
    {
        for(int i=0;i<Charactors.Count;++i)
        {
            if(i == _classNum)
            {
                Charactors[i].SetActive(true);
                if (!CharactorSelectUI.activeSelf)
                {
                    CharactorsAni[i].SetTrigger("Action");
                    ClassNum = _classNum;
                }
            }
            else
            {
                Charactors[i].SetActive(false);
            }
        }
    }

    public void CharactorOff()
    {
        for (int i = 0; i < Charactors.Count; ++i)
        {
            Charactors[i].SetActive(false);
        }
    }


    public void CharactorCreateUIOn()
    {
        CharactorCreateUI.SetActive(true);
        CharactorSelectUI.SetActive(false);
        CharactorOff();
    }
    public void CharactorCreateUIOff()
    {
        CharactorCreateUI.SetActive(false);
        CharactorSelectUI.SetActive(true);
        CharactorOff();
    }

    public void SetCreateName()
    {
        CreateName = CreateNameField.text;
    }

    public void CharactorCreate()
    {
        OutputMemoryStream os = new OutputMemoryStream();
        os.Write((short)Defines.CREATE_CHARACTOR);
        os.Write(GameManager.instance.UserName);
        os.Write(CreateName);
        os.Write((short)ClassNum);
        NetWork.instance.Send(os);
        CharactorCreateUIOff();
        SetCharactorList(CreateName, (short)ClassNum);
    }

    public void GameStart()
    {
        inGameOn = true;
    }
    
}
