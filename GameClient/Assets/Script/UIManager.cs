using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public Text text;
    public Player player;

    // Update is called once per frame
    void Update()
    {
        text.text = "X: " + player.transform.position.x + " Y: " + player.transform.position.y + " Z: " + player.transform.position.z;
    }
}
