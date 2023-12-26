using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerGhostCollision : MonoBehaviour
{
    private int playerLives = 1;

    private LayerMask ghostLayerMask;

    // Start is called before the first frame update
    void Start()
    {
        ghostLayerMask = LayerMask.GetMask("Ghost");
    }

    private void OnTriggerEnter(Collider other)
    {;
        if ((ghostLayerMask.value & 1 << other.gameObject.layer) != 0)
        {
            other.gameObject.SetActive(false);
            playerLives -= 1;
            CheckForDead();
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        GameObject other = collision.gameObject;
        if ((ghostLayerMask.value & 1 << other.layer) != 0)
        {
            other.SetActive(false);
            playerLives -= 1;
            CheckForDead();
        }
    }

    private void CheckForDead()
    {
        if (playerLives <= 0)
        {
            print("GAME OVER, player is dead");
            Time.timeScale = 0f;
        }
    }
}
