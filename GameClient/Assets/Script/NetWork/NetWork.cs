using System;
using System.Text;
using System.Net.Sockets;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ServerState
{
    NOT_CONNECTED,
    CONNECTED,
    LOGIN,
    CLOSING,
    ERROR,
}

public class NetWork : MonoBehaviour
{
    public static NetWork instance;

    //서버 상태
    public ServerState ST;

    public string IP;
    public int Port;

    public float Latency;
    private float timeStemp;
    private float startTime;

    private Resolve resolve;
    //비동기용 오브젝트
    public class AsyncObject
    {
        public byte[] Buffer;
        public Socket WorkingSocket;
        public AsyncObject(int BufferSize)
        {
            Buffer = new byte[BufferSize];
        }
    }

    private bool g_Connected;
    private Socket m_ClientSocket = null;

    //AsyncCallback : 해당 비동기 작업을 완료할 때 호출되는 메서드를 참조
    private AsyncCallback m_fnReceiveHandler;
    private AsyncCallback m_fnSendHandler;
    

    void Awake()
    {
        if(instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(this.gameObject);
        }
        DontDestroyOnLoad(this.gameObject);

        //비동기 작업 매서드를 초기화
        m_fnReceiveHandler = new AsyncCallback(handleDataReceive);
        m_fnSendHandler = new AsyncCallback(handleDataSend);
        resolve = new Resolve();

        Connect();
    }

    private void Update()
    {
        timeStemp += Time.deltaTime;
    }

    public bool Connected
    {
        get
        {
            return g_Connected;
        }
    }

    bool isConnected;

    public void ConnectToServer(string ip,int port)
    {
        //TCP 통신을 위한 소켓생성
        m_ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);
        m_ClientSocket.NoDelay = true;  //소켓 통신의 딜레이를 없앰
        isConnected = false;

        try
        {
            //연결시도
            m_ClientSocket.Connect(ip, port);
            isConnected = true;
        }
        catch
        {
            //연결 실패
            isConnected = false;
        }

        g_Connected = isConnected;

        if(isConnected)
        {
            //1024 바이트의 크기를 갖는 바이트 배열을 가진 AsynObjec 클래스를 생성
            AsyncObject ao = new AsyncObject(1024);

            //작업 중인 소켓을 저장하기 위해 socketClient 할당
            ao.WorkingSocket = m_ClientSocket;

            //비동기적으로 들어오는 자료를 수신하기 위해 BeginReceive 매서드 사용
            m_ClientSocket.BeginReceive(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnReceiveHandler, ao);

            Debug.Log("연결 성공!");
        }
        else
        {
            Debug.Log("연결 실패!");
        }
    }

    public void StopClient()
    {
        //클라이언트 소켓을 닫는다
        m_ClientSocket.Close();
    }

    public void Send(OutputMemoryStream os)
    {
        //추가 정보를 넘기기 위한 변수 선언
        AsyncObject ao = new AsyncObject(1);

        //OutputMemoryStream 사이즈 + short
        byte[] Header = BitConverter.GetBytes((short)(os.GetDataLength() + sizeof(short)));

        //OutputMemoryStream 사이즈와 short 2바이트 크기를 잡아서 할당
        byte[] packet = new byte[os.GetDataLength()+Header.Length];

        //해더 + OutputMemoryStream
        Array.Copy(Header, 0,packet, 0, Header.Length);
        Array.Copy(os.GetBuffer(), 0, packet, Header.Length, os.GetDataLength());

        ao.Buffer = packet;
        ao.WorkingSocket = m_ClientSocket;

        //전송시작
        try
        {
            //BeginSend : 연결된 Socket 데이터를 비동기로 보낸다
            m_ClientSocket.BeginSend(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnSendHandler, ao);
        }
        catch(Exception ex)
        {
            Debug.Log("전송 중 오류발생" + ex);
        }
    }


    //IAsyncResult : 비동기 작업의 상태를 나타내는 인터페이스
    private void handleDataReceive(IAsyncResult ar)
    {
        //넘겨진 추가 정보를 가져온다
        //AsyncState 속성의 자료형은 Object 형식이기 때문에 형 변환이 필요
        AsyncObject ao = (AsyncObject)ar.AsyncState;

        //받은 바이트 수 저장할 변수 선언
        int recvByte = 0;

        try
        {
            //자료를 수신하고, 수신받은 바이트를 가져옴
            recvByte = ao.WorkingSocket.EndReceive(ar);
        }
        catch
        {
            //예외가 발생하면 함수종료
            return;
        }

        //수신받은 자료의 크기가 1 이상일 때만 처리함
        if(recvByte >0)
        {
            //공백 문자들이 많이 발생할 수 있으므로, 받은 바이트 수 만큼 배열을 선언하고 복사함              
            byte[] msgByte = new byte[recvByte];

            Array.Copy(ao.Buffer, msgByte, recvByte);

            resolve.ReadMessage(msgByte, recvByte);
            if(startTime !=0)
            {
                Latency = timeStemp - startTime;
            }
            startTime = timeStemp;
        }

        try
        {
            //자료 처리가 끝났으면 다시 데이터를 수신받기 위해서 수신 대기를 한다
            //Begine 메서드를 이용해 비동기로 작업을 대기했다면
            //반드시 대리자 함수에서 End 메서드를 이용해 비동기 작업이 끝났다고 알려줘야함
            ao.WorkingSocket.BeginReceive(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnReceiveHandler, ao);
        }
        catch (Exception ex)
        {
            //예외가 발생하면 예외 정보를 출력 후 함수를 종료한다
            Debug.Log("자료 수신 대기 도중 오류 발생 ! 메시지 :" + ex.Message);
            return;
        }
    }

    private void handleDataSend(IAsyncResult ar)
    {
        //넘겨진 추가 정보를 가져온다
        AsyncObject ao = (AsyncObject)ar.AsyncState;

        //보낸 바이트 수를 저장할 변수 선언
        int sendBytes;

        try
        {
            //자료를 전송하고, 전송한 바이트를 가져온다
            sendBytes = ao.WorkingSocket.EndSend(ar);
        }
        catch (Exception ex)
        {
            //예외가 발생하면 예외 정보 출력 후 함수를 종료한다
            Debug.Log("자료 송신 도중 오류 발생! 메시지 : " + ex.Message);
            return;
        }

        if (sendBytes > 0)
        {
            //여기도 마찬가지로 보낸 바이트 수 만큼 배열 선언 후 복사한다.
            byte[] msgByte = new byte[sendBytes];
            Array.Copy(ao.Buffer, msgByte, sendBytes);
            Debug.Log("메시지 보냄 : " + sendBytes);
        }
    }

    public void Connect()
    {
        if (ST == ServerState.NOT_CONNECTED)
        {
            ConnectToServer(IP, Port);

            if (!Connected)
            {
                Debug.Log("접속 중 오류 발생!");
                return;
            }
            else
            {
                Debug.Log("접속 성공!");
                ST = ServerState.CONNECTED;
            }
        }
    }

    private void OnApplicationQuit()
    {
        OutputMemoryStream os = new OutputMemoryStream();
        os.Write((short)Defines.USER_OUT);
        os.Write(PlayerManager.instance.playerName);
        Send(os);
        StopClient();
    }
}
