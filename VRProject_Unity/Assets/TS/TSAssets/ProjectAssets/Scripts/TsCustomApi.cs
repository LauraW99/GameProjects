using PlasticGui.WorkspaceWindow.PendingChanges;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using TsAPI.Types;
using TsSDK;
using UnityEditor.VersionControl;
using UnityEngine;
using UnityEngine.Playables;

public class TsCustomApi : MonoBehaviour
{


    public enum AnimationAssetEnum
    {
        ChargeL, 
        ChargeR,
        ShootL,
        ShootR,
        Puddle,
        Pendant
    }

    [SerializeField]
    TsHapticPlayer m_tsHapticPlayer;

    TsRoot tsRoot;

    IAssetManager assetManager;
    IHapticPlayable playable;
    IHapticAsset hapticAnimationAsset;
    string assetPath;
    string animationPath;
    private bool assetLoaded = false;

    // Start is called before the first frame update
    void Start()
    {
        tsRoot = TsManager.Root;
        assetManager = tsRoot.AssetManager;

        
        if(m_tsHapticPlayer == null)
        {
            Debug.Log("HapticPlayer in CustomApi is Null");
        }

        if (assetManager == null)
        {
            Debug.Log("AssetManager in CustomApi is Null");
        }

        assetPath = Application.dataPath;
        animationPath = assetPath + "/TS/TSAssets/ProjectAssets/AnimationAssets/";
    }

    void Update()
    {
        if(playable != null)
        {
            if (!playable.IsPlaying & assetLoaded)
            {
                
                assetManager.Unload(hapticAnimationAsset);
                assetLoaded = false;
            }
        }
    }


    private IHapticAsset LoadAsset(string FileName)
    {
        string path = this.animationPath + FileName + ".ts_asset";

        

        print(path);
        IHapticAsset asset = assetManager.Load(path) as IHapticAsset;
        if(asset != null)
        {
            assetLoaded = true;
            return asset;
        }
        return null;
    }

    public void Play()
    {
        PlayAnimationAsset(AnimationAssetEnum.ShootR);
    }

    public void Stop()
    {
        if(playable != null && playable.IsPlaying)
        {
            playable.Stop();
            playable.IsLooped = false;
            assetManager.Unload(hapticAnimationAsset);
            assetLoaded = false;
        }
    }

    public void LoopAsset()
    {
        playable.IsLooped = true;
    }

    public void PlayAnimationAsset(AnimationAssetEnum animationAsset)
    {
        hapticAnimationAsset = LoadAsset(animationAsset.ToString());
        print(animationAsset);
        if(hapticAnimationAsset != null)
        {
            playable = m_tsHapticPlayer.GetPlayable(hapticAnimationAsset);

            if(playable != null)
            {
                playable.Play();
            }
            

        }
        
    }

    public void ChangeMultiplier(TsHapticParamType param, float multiplier)
    {
  
        List<TsHapticParamMultiplier> tempMultipliers = playable.Multipliers.ToList();

        for (int i = 0; i < tempMultipliers.Count; ++i)
        {
            if (tempMultipliers[i].type == param)
            {
                tempMultipliers[i] = new TsHapticParamMultiplier(param, multiplier);
            }
        }
        //Debug.Log("Multiplier "+param+" changed to: " + multiplier);

        playable.Multipliers = tempMultipliers;
    }

    public bool IsPlaying()
    {
        if (playable != null)
        {
            return playable.IsPlaying;
        }
        return false;
    }


}
