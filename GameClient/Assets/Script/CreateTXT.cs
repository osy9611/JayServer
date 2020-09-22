using System;
using System.Text;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]


public class CreateTXT : MonoBehaviour
{
    public Vector3 gridweorldSize;

    //월드를 분할하기 위한 함수
    public float nodeRadius;
    float nodeDiameter;
    public int gridSizeX, gridSizeZ;

    public List<GameObject> divisionCol = new List<GameObject>();

    [SerializeField]
    public List<Node> node = new List<Node>();
    public string filePath;
    string textValue;
    
    public GameObject a;

    // Start is called before the first frame update
    void Awake()
    {
        nodeDiameter = nodeRadius * 2;

        gridSizeX = Mathf.RoundToInt(gridweorldSize.x / nodeDiameter);
        gridSizeZ = Mathf.RoundToInt(gridweorldSize.z / nodeDiameter);

        CreateNode();
    }

    private void Start()
    {
        Invoke("SetTextFile", 5.0f);
    }

    void CreateNode()
    {
        Vector3 worldBottomLeft = transform.position - Vector3.right * gridweorldSize.x / 2 - Vector3.forward * gridweorldSize.z / 2;
        for (int z = 0; z < gridSizeZ; ++z)
        {
            for (int x = gridSizeX - 1; x >= 0; --x)
            {
                Vector3 worldPoint = worldBottomLeft + Vector3.right * (x * nodeDiameter + nodeRadius) + Vector3.forward * (z * nodeDiameter + nodeRadius);
                a.transform.localScale = Vector3.one * (nodeDiameter);
                GameObject obj =  Instantiate(a, worldPoint, Quaternion.identity);
                Node dummy = obj.GetComponent<Node>();
                dummy.sx = worldPoint.x - nodeRadius;
                dummy.sy = worldPoint.z + nodeRadius;
                dummy.ex = worldPoint.x + nodeRadius;
                dummy.ey = worldPoint.z - nodeRadius;              
                node.Add(dummy);               
            }
        }
    }
    void SetTextFile()
    {
        FileStream fs = new FileStream(filePath, FileMode.Create);
        StreamWriter sw = new StreamWriter(fs);
        sw.WriteLine(node.Count+";");
        for (int i = node.Count - 1; i >= 0; --i)
        {
            sw.WriteLine(node[i].sx + ";" + node[i].sy + ";" + node[i].ex + ";" + node[i].ey + ";");
            sw.WriteLine(node[i].obj.Count + ";");
            for(int j=0;j< node[i].obj.Count;++j)
            {
                sw.WriteLine(node[i].obj[j].colObj.transform.position.x + ";" + node[i].obj[j].colObj.transform.position.y + ";" + node[i].obj[j].colObj.transform.position.z + ";"
                    + node[i].obj[j].CT + ";" + node[i].obj[j].radius + ";");
            }
        }
        Debug.Log("파일 생성 성공!!");
        sw.Close();
        fs.Close();
    }

    private void OnDrawGizmos()
    {
        Gizmos.DrawWireCube(transform.position, new Vector3(gridweorldSize.x, 1, gridweorldSize.z));
    }
}
