using System.Collections;
using System.Collections.Generic;
using UnityEngine;

struct Data
{
    public short type;
    public string Name;
    public int Level;
}
public class TestStream : MonoBehaviour
{
    Data data;
    OutputMemoryStream output;
    InputMemoryStream input;

    public string Name;
    public int Level;
    // Start is called before the first frame update
    void Start()
    {
        data.Name = "osy9611";
        data.type = 1500;
        data.Level = 1;
        output = new OutputMemoryStream();

        output.Write(data.type);
        output.Write(data.Name);
        output.Write(data.Level);
        

        int outputSize = output.GetDataLength();
        
        input = new InputMemoryStream(output.GetBuffer(),output.GetDataLength());
        input.Read(ref Name);
        input.Read(ref Level);
        //Debug.Log(input.GetHeadSize());
    }
    
    public void SendDdata()
    {
        NetWork.instance.Send(output);
    }
}
