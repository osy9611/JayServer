using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[System.Serializable]
public class CharactorUIData : MonoBehaviour
{
    public RobbyUI _robbyUI;
    public Text Name;
    public Text ClassLevel;
    public int ClassNum = 0;
    bool isShow;

    private void Start()
    {
        _robbyUI = FindObjectOfType<RobbyUI>();
    }

    private void Update()
    {
        if (isShow)
        {
            isShow = false;
            if(!_robbyUI.isShow(ClassNum))
            {
                Debug.Log("들어옴");
                _robbyUI.CharactorOn(ClassNum);
            }
        }
    }

    public void SetText(string _name, int _level,int _class)
    {
        Name.text = _name;
        ClassLevel.text = "직업 : " + _class + " 레벨 : " + _level;
        ClassNum = _class;
    }

    public void ShowChactor()
    {
        isShow = true;
    }


}
