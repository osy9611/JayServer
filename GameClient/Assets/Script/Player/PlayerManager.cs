using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    public static PlayerManager instance;

    public string playerName;

    public Dictionary<string, Player> PlayerList = new Dictionary<string, Player>();

    public GameObject Player;

    private bool IsSet = false;
    private string  _setName;
    private Vector3 _setPos;
    private float _setRot;

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
        if (IsSet)
        {
            GameObject obj = Instantiate(this.Player, _setPos, Quaternion.identity);
            obj.GetComponent<Player>().SetName(_setName);
            IsSet = false;
        }
    }

    public void SetPlayer(Player _player)
    {
        PlayerList.Add(_player.Name, _player);
    }

    public void SearchPlayer(string _name, Vector3 _pos, Vector3 _dir, float _rot)
    {
        if (PlayerList.ContainsKey(_name))
        {
            PlayerList[_name].SetPos(_pos, _dir, _rot);
        }
        else
        {
            _setName = _name;
            _setPos = _pos;
            _setRot = _rot;
            IsSet = true;
        }
    }
}
