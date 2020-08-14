using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OutputMemoryStream
{
    public byte[] mBuffer;
    public int mHead = 0;
    private int mCapacity = 0;
    
    public OutputMemoryStream() { ReallocBuffer(1500 * 8); }
    public byte[] GetBuffer() { return mBuffer; }
    public int GetDataLength() { return mHead; }

    private void ReallocBuffer(int inNewDataLength)
    {
        if(mBuffer == null)
        {
            mBuffer = new byte[inNewDataLength];
        }
        else
        {
            byte[] tempBuffer = new byte[inNewDataLength];
            Array.Clear(tempBuffer, 0, inNewDataLength);
            Buffer.BlockCopy(mBuffer, 0, tempBuffer, 0, inNewDataLength);
            mBuffer = tempBuffer;
        }

        mCapacity = inNewDataLength;
    }

    public void Write(short inData, int inDataCount = sizeof(short))
    {
        Buffer.BlockCopy(BitConverter.GetBytes(inData), 0, mBuffer, mHead, inDataCount);
        mHead += inDataCount;
    }

    public void Write(int inData,int inDataCount = sizeof(int))
    {
        Buffer.BlockCopy(BitConverter.GetBytes(inData), 0, mBuffer, mHead, inDataCount);
        mHead += inDataCount;
    }

    public void Write(float inData, int inDataCount = sizeof(float))
    {
        Buffer.BlockCopy(BitConverter.GetBytes(inData), 0, mBuffer, mHead, inDataCount);
        mHead += inDataCount;
    }

    public void Write(string inString)
    {
        short elementCount = (short)inString.Length;
        Write(elementCount);
        Buffer.BlockCopy(Encoding.UTF8.GetBytes(inString), 0, mBuffer, mHead, elementCount);
        mHead += elementCount;
    }
}

public class InputMemoryStream
{
    private byte[] mBuffer;
    private int mCapapcity;
    private int mHead = Defines.HEADERSIZE;
    
    public InputMemoryStream(byte[] inBuffer,int inDataCount)
    {
        mBuffer = new byte[inBuffer.Length];
        mBuffer = (byte[])inBuffer.Clone();
        mCapapcity = inDataCount;
    }

    public byte[] GetBfferPtr() { return mBuffer; }
    public int GetRemainingDataCount() { return mCapapcity - mHead; }
    public int GetHeadSize() { return mHead;}
    public void ResetToCapacity(int inDataCapacity) { mCapapcity = inDataCapacity; mHead = 0; }

    public void Read(ref short inData,int inDataCount = sizeof(short))
    {
        inData = BitConverter.ToInt16(mBuffer, mHead);
        mHead += sizeof(short);
    }

    public void Read(ref int inData, int inDataCount = sizeof(int))
    {
        inData = BitConverter.ToInt32(mBuffer, mHead);
        mHead += sizeof(int);
    }

    public void Read(ref float inData, int inDataCount = sizeof(float))
    {
        inData = BitConverter.ToSingle(mBuffer, mHead);
        mHead += sizeof(float);
        Debug.Log(mHead);
    }

    public void Read (ref Vector3 inData)
    {
        Read(ref inData.x);
        Read(ref inData.y);
        Read(ref inData.z);
    }

    public void Read(ref string inString)
    {
        short elementCount = 0;
        Read(ref elementCount);
        inString = Encoding.UTF8.GetString(mBuffer, mHead, elementCount);
        mHead += elementCount;
    }
}
