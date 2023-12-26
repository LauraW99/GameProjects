using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PuddleCollision : MonoBehaviour
{
    [SerializeField] TsCustomApi tsCustomApi;

    private bool tsAnimationPlaying = false;
    private float animationDuration = 1f;
    private Coroutine puddleAnimationCoroutine;

    private LayerMask mask;


    private void Start()
    {
        mask = LayerMask.GetMask("Player");
    }

    private void OnTriggerStay(Collider other)
    {
        if ((mask.value & 1 << other.gameObject.layer) != 0)
        {
            GetComponent<Renderer>().material.EnableKeyword("_EMISSION");
            //Teslasuit Script
            if (!tsAnimationPlaying)
            {
                puddleAnimationCoroutine = StartCoroutine(PlayPuddleAnimation());
            }
        }
    }

    private IEnumerator PlayPuddleAnimation()
    {
        tsAnimationPlaying = true;
        tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.Puddle);
        yield return new WaitForSeconds(animationDuration);
        tsAnimationPlaying = false;
    }

    private void OnTriggerExit(Collider other)
    {
        if ((mask.value & 1 << other.gameObject.layer) != 0)
        {
            GetComponent<Renderer>().material.DisableKeyword("_EMISSION");
            StopCoroutine(puddleAnimationCoroutine);
            tsAnimationPlaying = false;
            tsCustomApi.Stop();
        }
    }
}
