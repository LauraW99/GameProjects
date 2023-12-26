using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem.XR;
using UnityEngine.XR.Interaction.Toolkit;

public class PlayerPickupObjects : MonoBehaviour
{
    public static bool pickedUpBoots = false;
    public static bool pickedupGloves = false;
    public static bool pickedUpAmulet = false;
    public static bool pickedUpCapacitor = false;

    private Gradient gradient;
    XRInteractorLineVisual[] m_LineVisuals;
    private void Start()
    {
        gradient = new Gradient();
    }

    public void PickUpBoots()
    {
        pickedUpBoots = true;
        Physics.IgnoreLayerCollision(3, 6, true);

    }

    public void PickUpGloves()
    {
        pickedupGloves = true;
        SetLineVisualColor(Color.white);
    }

    public void PickUpAmulet()
    {
        pickedUpAmulet = true;
    }

    public void PickUpCapacitor()
    {
        pickedUpCapacitor = true;
        SetLineVisualColor(Color.white);
    }

    private void SetLineVisualColor(Color color)
    {
        var colors = new GradientColorKey[2];
        colors[0] = new GradientColorKey(color, 0.0f);
        colors[1] = new GradientColorKey(color, 1.0f);
        var alphas = new GradientAlphaKey[2];
        alphas[0] = new GradientAlphaKey(1.0f, 0.0f);
        alphas[1] = new GradientAlphaKey(0.0f, 1.0f);
        gradient.SetKeys(colors, alphas);

        m_LineVisuals = GetComponentsInChildren<XRInteractorLineVisual>();
        if (m_LineVisuals != null)
        {
            foreach (XRInteractorLineVisual lineVisual in m_LineVisuals)
            {
                if (lineVisual != null)
                {
                    lineVisual.invalidColorGradient = gradient;
                    lineVisual.validColorGradient = gradient;
                }
            }
        }
    }
}
