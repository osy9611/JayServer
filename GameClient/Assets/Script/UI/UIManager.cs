using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    private string id;
    private string pw;

    public InputField idInputField;
    public InputField pwInputField;


    public void SetId()
    {
        id = idInputField.text;
    }

    public void SetPw()
    {
        pw = pwInputField.text;
    }

    public void Connet()
    {
        NetWork.instance.Connect();
        OutputMemoryStream os = new OutputMemoryStream();
        os.Write((short)Defines.LOGIN_CHECK);
        os.Write(id);
        os.Write(pw);
        NetWork.instance.Send(os);
    }
}
