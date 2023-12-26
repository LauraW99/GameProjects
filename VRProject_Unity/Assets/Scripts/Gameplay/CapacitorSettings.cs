using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Interaction.Toolkit;

public class CapacitorSettings : MonoBehaviour
{
    [SerializeField] TsCustomApi tsCustomApi;

    static private bool charged = false;

    static XRInteractorLineVisual[] m_LineVisuals;
    static Gradient gradient = new Gradient();

    private void Start()
    {
        m_LineVisuals = GetComponentsInChildren<XRInteractorLineVisual>();
    }

    public static bool isCharged() { return charged; }

    public static void Charge()
    {
        charged = true;
        SetGradientColor(Color.blue);
    }

    public static void Unload()
    {
        charged = false;
        SetGradientColor(Color.white);
    }

    private static void SetGradientColor(Color color)
    {
        var colors = new GradientColorKey[2];
        colors[0] = new GradientColorKey(color, 0.0f);
        colors[1] = new GradientColorKey(color, 1.0f);
        var alphas = new GradientAlphaKey[2];
        alphas[0] = new GradientAlphaKey(1.0f, 0.0f);
        alphas[1] = new GradientAlphaKey(0.0f, 1.0f);
        gradient.SetKeys(colors, alphas);

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
