using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node : MonoBehaviour
{
    public float sx, sy, ex, ey;
    public List<GameObject> obj;

    private void Awake()
    {
        obj = new List<GameObject>();
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "ColCheckObj")
        {
            obj.Add(other.gameObject);
        }
    }
}
