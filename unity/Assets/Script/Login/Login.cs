using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using GameClient;

public class Login : MonoBehaviour
{
    Button start_btn;
    InputField role_name;
    InputField role_key;

    void Start()
    {
        start_btn = GameObject.Find("button").GetComponent<Button>();
        start_btn.onClick.AddListener(delegate()
        {
            OnClick();
        });
        role_name = GameObject.Find("name").GetComponent<InputField>();
        role_key = GameObject.Find("password").GetComponent<InputField>();
    }

    // µã»÷µÇÂ¼°´Å¥
    private void OnClick()
	{
        ClientSocket sock = ClientSocket.GetInstance();
        ProtoLogin proto = new ProtoLogin();
        proto.id = 1;
        proto.name = role_name.text;
        proto.password = role_key.text;
        byte[] msg = Pack.PackMsg(proto);
        Debug.Log(role_name.text);
        Debug.Log(role_key.text);
        sock.AsynSend(msg);
	}
}
