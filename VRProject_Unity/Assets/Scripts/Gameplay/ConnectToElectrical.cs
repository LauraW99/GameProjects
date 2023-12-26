using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.WSA;
using UnityEngine.XR;
using UnityEngine.XR.Interaction.Toolkit;


public enum HandSide
{
    leftHand,
    rightHand
}

public class ConnectToElectrical : MonoBehaviour
{
    
    //public static bool isConnected = false;

    [SerializeField] private HandSide handSide;

    [SerializeField] TsCustomApi tsCustomApi;

    [SerializeField] GameObject otherController;
    XRRayInteractor interactor;
    XRInteractorLineVisual lineVisual;

    private static float activeLineLength = 30f;
    private static float inactiveLineLength = 10f;
    private static float activeLineWidth = 0.01f;
    private static float inactiveLineWidth = 0.003f;
    
    private float shootLoadTime = 1.5f;
    private float shootDuration = 0.5f;
    private bool isShooting = false;
    private Coroutine shootCoroutine;

    private LayerMask mask;
    Gradient gradient;

    private void Start()
    {
        if(otherController != null)
        {
            interactor = otherController.GetComponentInChildren<XRRayInteractor>();
            lineVisual = otherController.GetComponentInChildren<XRInteractorLineVisual>();
        }

        mask = LayerMask.GetMask("Electrical");
        gradient = new Gradient(); 
    }

    private void OnTriggerStay(Collider other)
    {
        if (lineVisual != null && (mask.value & 1 << other.gameObject.layer) != 0)
        {
            if (!PlayerPickupObjects.pickedUpCapacitor && PlayerPickupObjects.pickedupGloves)
            {
                if (!isShooting)
                {
                    shootCoroutine = StartCoroutine(ShootStationary(handSide));
                }
            }
            else if (PlayerPickupObjects.pickedUpCapacitor && !CapacitorSettings.isCharged())
            {
                CapacitorSettings.Charge();
                if (handSide == HandSide.leftHand)
                {
                    print("Should charge left");
                    tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.ChargeL);
                    
                }
                else
                {
                    print("Should charge right");
                    tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.ChargeR);
                }
            }

        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (lineVisual != null && (mask.value & 1 << other.gameObject.layer) != 0 && PlayerPickupObjects.pickedupGloves)
        {
            if(shootCoroutine != null)
            {
                StopCoroutine(shootCoroutine);
            }
            
            StopShoot();
            tsCustomApi.Stop();
        }   
    }

    private void SetGradientColor(Color color)
    {
        var colors = new GradientColorKey[2];
        colors[0] = new GradientColorKey(color, 0.0f);
        colors[1] = new GradientColorKey(color, 1.0f);
        var alphas = new GradientAlphaKey[2];
        alphas[0] = new GradientAlphaKey(1.0f, 0.0f);
        alphas[1] = new GradientAlphaKey(0.0f, 1.0f);

        gradient.SetKeys(colors, alphas);
        lineVisual.invalidColorGradient = gradient;
    }

    private IEnumerator ShootStationary(HandSide handSide)
    {
        isShooting = true;
        if (handSide == HandSide.leftHand)
        {
            tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.ChargeL);
        } else
        {
            tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.ChargeR);
        }
        yield return new WaitForSeconds(shootLoadTime);
        StartShoot(handSide);
        yield return new WaitForSeconds(shootDuration);
        StopShoot();
    }

    private void StartShoot(HandSide handSide)
    {
        SetGradientColor(Color.cyan);
        lineVisual.lineLength = activeLineLength;
        lineVisual.lineWidth = activeLineWidth;

        ElectricalConnection.isConnected = true;
        if (handSide == HandSide.leftHand)
        {
            tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.ShootR);
        }
        else
        {
            tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.ChargeL);
        }
    }

    private void StopShoot()
    {
        if(!PlayerPickupObjects.pickedUpCapacitor)
        {
            SetGradientColor(Color.white);
            lineVisual.lineLength = inactiveLineLength;
            lineVisual.lineWidth = inactiveLineWidth;
        }
        ElectricalConnection.isConnected = false;
        isShooting = false;
    }
}
