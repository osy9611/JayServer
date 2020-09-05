using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class LogInUI : MonoBehaviour
{
    public static LogInUI instance;

    //로그인용
    private string id;
    private string pw;

    //회원 가입용
    private string signId;
    private string signPw;

    public InputField idInputField;
    public InputField pwInputField;

    public InputField signUpIdInputField;
    public InputField signUpPwInputField;

    public GameObject SignUpPanel;
    private bool PanelObjectOn;
    public Text _systemMessage;

    bool _textOn;

    bool robbyOn = false;
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
        TextSet();

        if (!PanelObjectOn)
        {
            signUpIdInputField.text = "";
            signUpPwInputField.text = "";
        }
        SignUpPanel.SetActive(PanelObjectOn);

        if(robbyOn)
        {
            robbyOn = false;
            SceneManager.LoadScene("Robby");
        }
    }
    public void SetId()
    {
        if(SignUpPanel.activeSelf)
        {
            signId = signUpIdInputField.text;
        }
        else
        {
            id = idInputField.text;
        }
  
    }

    public void SetPw()
    {
        if (SignUpPanel.activeSelf)
        {
            signPw = signUpPwInputField.text;
        }
        else
        {
            pw = pwInputField.text;
        }
    }

    public void LoginCheckAndConnet()
    {
        if(string.IsNullOrEmpty(id) || string.IsNullOrEmpty(pw))
        {
            _systemMessage.text = "아이디 또는 패스워드를 기입하지 않았습니다";
        }
        else
        {
            NetWork.instance.Connect();
            OutputMemoryStream os = new OutputMemoryStream();
            os.Write((short)Defines.LOGIN_CHECK);
            os.Write(id);
            os.Write(pw);
            NetWork.instance.Send(os);
        }
    }

    public void SignUpPanelOn()
    {
        PanelObjectOn = true;
    }

    public void SignUpPanelOff()
    {
        PanelObjectOn = false;
        signId = "";
        signPw = "";
    
    }

    public void SignUpAndConnect()
    {
        if (string.IsNullOrEmpty(signId) || string.IsNullOrEmpty(signPw))
        {
            _systemMessage.text = "아이디 또는 패스워드를 기입하지 않았습니다";
        }
        else
        {
            NetWork.instance.Connect();
            OutputMemoryStream os = new OutputMemoryStream();
            os.Write((short)Defines.SIGN_UP);
            os.Write(signId);
            os.Write(signPw);
            NetWork.instance.Send(os);
        }
    }

    public void LogInResultCheck(InputMemoryStream io)
    {
        bool result = false;
        io.Read(ref result);
      
        if(result)
        {
            Debug.Log("LogIn result : " + result);
            GameManager.instance.UserName = id;
            GameManager.instance.StoreCharactorData(io);
            robbyOn = true;
        }
        else
        {
            _systemMessage.text = "회원 정보가 없습니다.";
        }
    }

    public void SignInResultCheck(InputMemoryStream io)
    {
        bool result = false;
        io.Read(ref result);
        Debug.Log("SignUp result : " + result);
        if (result)
        {
            SignUpPanelOff();
        }
        else
        {
            _systemMessage.text = "회원 정보가 이미 있습니다";
        }
    }

    private void TextSet()
    {
        if (_systemMessage.text != "")
        {
            StartCoroutine(TextOn());
        }
    }

    IEnumerator TextOn()
    {
        _textOn = false;
        yield return new WaitForSeconds(1.0f);
        _systemMessage.text = "";
    }
}
