using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 * 네트워크 특성상 서버에서 보내는 데이터를 클라이언트는 패킷 단위로 받지 않는다. 한 번에 모두 받을 수 잇고
 * 여러 번 나눠서 받을 수 있다(즉, 서버는 send를 두 번 했는데, 클라에서는 receive 한 번만 발생하는 경우가 생김)
 * 이런 경우를 처리하기 위해서 먼저 받은 데이터를 PacketBuffer에 저장한 후 클라이언트에서 동시에 여러번 요청하면서 서버는
 * 우선 처리하지 않고 남겨 놓았다가 다음에 받은 데이터와 연결하여 처리
 */

public class Defines
{
    public static readonly short HEADERSIZE = sizeof(short);    //헤더 사이즈

    public static readonly short USER_DATA = 1500;
}
public class Resolve
{
    byte[] PacketBuffer = new byte[2048];

    int PacketBufferMarker;
    int remain_byte;

    byte[] Header = new byte[Defines.HEADERSIZE];
    public Resolve()
    {
        this.PacketBufferMarker = 0;
        this.remain_byte = 0;
    }

    public void ReadMessage(byte[] msgByte,int recvBytes)
    {
        this.remain_byte = recvBytes;

        //받은 데이터를 패킷 버퍼에 저장한다
        Array.Copy(msgByte, 0, PacketBuffer, PacketBufferMarker, recvBytes);

        int nPacketData = this.PacketBufferMarker + msgByte.Length;
        int nReadData = 0;

        while(nPacketData>0) //받은 데이터를 모두 처리할 때까지 반복한다.
        {
            //남은 데이터가 패킷 헤더보다 작으면 중단한다.
            if(nPacketData < Defines.HEADERSIZE)
            {
                break;
            }

            Array.Copy(PacketBuffer, nReadData, Header, 0, Defines.HEADERSIZE);
            int size = BitConverter.ToInt16(Header, 0);

            if(size<=nPacketData) //일단 처리할 수 있는 만큼의 데이터가 있다면 패킷을 처리한다.
            {
                InputMemoryStream io = new InputMemoryStream(msgByte, recvBytes);
                CheckData(io,size);
                nPacketData -= size;
                nReadData += size;
            }
            else
            {
                break; //패킷으로 처리할 수 없는 만큼이 아니면 중단한다.
            }
        }

        if(nPacketData>0)   //만약 패킷 데이터 크기가 남았다면 다시 패킷 데이터에 다시 넣어줌
        {
            byte[] TempBuffer = new byte[2048];
            Array.Copy(PacketBuffer, nReadData, TempBuffer, 0, nPacketData);
            Array.Copy(TempBuffer, 0, PacketBuffer, 0, nPacketData);
        }
    }

    void CheckData(InputMemoryStream inInputStream,int size)
    {
        short type = 0;
        inInputStream.Read(ref type);

        switch (type)
        {
            case 1500:
                MonsterManager.instance.SetMonster(inInputStream);
                //int _id = 0;
                //float x = 0, y = 0, z = 0, rot = 0;
                //inInputStream.Read(ref _id);
                //inInputStream.Read(ref x);
                //inInputStream.Read(ref y);
                //inInputStream.Read(ref z);
                //inInputStream.Read(ref rot);
                //Debug.Log("ID : " + _id + " x :" + x + " y : " + y + "z : " + z);
                //MonsterManager.instance.SearchMonster(_id, new Vector3(x, y, z));
                break;
        }

    }
}
