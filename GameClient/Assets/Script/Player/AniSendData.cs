using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 * 캐릭터 애니메이션이 재생될때 특정 이벤트를 발생 시켜야 한다면
 * 사용하기 위함
 */
public class AniSendData : MonoBehaviour
{
    public bool isAttack;
    private bool prevIsAttack;
    
    // Update is called once per frame
    void Update()
    {
        CheckAttack();
    }

    void CheckAttack()
    {
        if(isAttack)
        {
            if(isAttack != prevIsAttack)
            {
                MonsterManager.instance.Write(this.gameObject.transform.root.name);
                prevIsAttack = isAttack;
            }
        }
        else
        {
            prevIsAttack = false;
        }
    }
}
