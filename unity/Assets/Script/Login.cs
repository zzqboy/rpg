using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Login : MonoBehaviour {
	
	// Use this for initialization
	void Start () {
		Button login_btn = this.GetComponent<Button>();
		login_btn.onClick.AddListener(this.OnClick);
	}

	// µã»÷µÇÂ¼°´Å¥
	void OnClick()
	{ 
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
