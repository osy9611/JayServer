# JayServer
IOCP를 이용한 게임서버
+ 사용 기술
  + Unity 3D
  + C/C++, C#
  + IOCP
  + MySQL

+ 작업내용
  + Lobby Server
    + 로그인 확인 요청이 들어오면 ID, PW 데이터를 DB Server로 전송
    + DB 서버에서 로그인 결과 및 캐릭터 정보를 받아와 클라이언트에게 정보를 전달
    + 회원가입 요청이 잇다면 ID, PW 데이터와 현재 서버에 할당되어있는 SessingId를 DB서버에 보냄
    + DB로 보낸 패킷의 결과를 받으면 SessionID에 데이터를 전송함
    + 캐릭터 생성 요청이 있으면 ID, 캐릭터 이름, 클래스 정보 데이터 패킷을 만들어 DB서버에 전송
  + Game Server
    + Area Manager
      + 충돌 체크를 위해 맵을 분할한 데이터를 읽고 데이터를 저장하도록 구현
    + Object Manager
      + 몬스터, 유저 오브젝트 업데이트 관리와 클라이언트로 오브젝트 데이터를 보내주는 ObjectManager 구현
    + 클라이언트에서 받은 패킷을 직렬화 및 역직렬화하는 OutputStream,InputStream 구현
  + DB Server
    + ID, PW 데이터를 받아 Database에 검색 후 결과를 Lobby Server로 보내주도록 구현
    + 회원 가입 시 DB안에 데이터와 중복되는 계정이 있는지 찾고 결과르 보내주도록 구현
    + Lobby Server에서 선택한 캐릭터의 이전 위치를 DB에서 받아와 보내주도록 구현
  + Client
    + Server로 패킷을 보내기위한 직렬화 / 역직렬화를 하는 MemoryStream 구현
    + Player가 일정 시간이 지난 후 방향을 체크해 다른 방향일 경우 서버에 이동 패킷을 보내도록 구현
    + 서버에서 들어온 캐릭터 방향과 위치를 예측해 이동 위치를 계산하도록 구현
    
+ 서버구조
  ![image](https://user-images.githubusercontent.com/55786364/224944353-5961a408-217a-40c1-ba62-766c04a761ea.png)

