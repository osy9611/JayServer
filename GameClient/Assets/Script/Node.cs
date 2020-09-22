using System.Collections;
using System.Collections.Generic;
using UnityEngine;

enum ColliderType
{
    Capsule,
    Box,
    Sphere
}

public struct ColliderData
{
    public GameObject colObj;
    public int CT;
    public float radius;
}

public class Node : MonoBehaviour
{
    public float sx, sy, ex, ey;
    public List<ColliderData> obj;

    private void Awake()
    {
        obj = new List<ColliderData>();
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "ColCheckObj")
        {
            ColliderData col = new ColliderData();
            col.colObj = other.gameObject;
            if(other.GetComponent<CapsuleCollider>() !=null)
            {
                col.CT = (int)ColliderType.Capsule;
                col.radius = other.GetComponent<CapsuleCollider>().radius;
            }
            else if (other.GetComponent<BoxCollider>() != null)
            {
                col.CT = (int)ColliderType.Box;
            }
            else if (other.GetComponent<SphereCollider>() != null)
            {
                col.CT = (int)ColliderType.Sphere;
                col.radius = other.GetComponent<SphereCollider>().radius;
            }
            obj.Add(col);
        }
    }
}
