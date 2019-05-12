using UnityEngine;
using UnityEngine.UI;

public class Login : MonoBehaviour {

    void Start () {
        Button btn = GameObject.Find("button").GetComponent<Button>();
        btn.onClick.AddListener(
            delegate() { this.OnClick(); }
            );
	}

	// µã»÷µÇÂ¼°´Å¥
	public void OnClick()
	{
        Debug.Log("hello123");
	}
}
