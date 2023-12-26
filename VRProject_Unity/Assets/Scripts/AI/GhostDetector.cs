using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using Unity.VisualScripting;
using UnityEngine;

public class GhostDetector : MonoBehaviour
{

    public TsCustomApi tsCustomApi;

    public GameObject bodyCenterReference;
    public GameObject leftController;
    public GameObject camera;


    private bool amuletActive = false;
    private List<GameObject> ghostList = new List<GameObject>();
    private GameObject nearestGhost;
    private Vector3 headPos;

    private int minRaiseAngle = 60;
    private float maxDistance = 25;

    // Start is called before the first frame update
    void Start()
    {

        GetGhosts();
    }

    // Update is called once per frame
    void Update()
    {
        if(!PlayerPickupObjects.pickedUpAmulet) { return; }
        headPos = camera.transform.position;
        Vector3 horizontal = (leftController.transform.position - headPos);
        horizontal.y = 0;
        float leftHandVerticalAngle = Vector3.Angle(horizontal ,leftController.transform.position - headPos);

        if(leftHandVerticalAngle < 90-minRaiseAngle)
        {amuletActive=true;} else  { amuletActive=false; }


        if (amuletActive && (bodyCenterReference != null && ghostList.Count > 0))
        {
            
            Vector3 bodyReferencePosition = bodyCenterReference.transform.position;
            float minDistance = float.MaxValue;
            foreach (GameObject ghost in ghostList)
            {
                if (!ghost.gameObject.activeSelf)
                {
                    continue;
                }
                float temp_distance = Vector3.Distance(bodyReferencePosition, ghost.transform.position);


                if (temp_distance < minDistance)
                {
                    nearestGhost = ghost;
                    minDistance = temp_distance;
                }

                

            }

           
            Vector3 t_handVector =  bodyReferencePosition - leftController.transform.position;
            Vector3 t_ghostVector = bodyReferencePosition - nearestGhost.transform.position;

            Vector2 handVector = new(t_handVector.x, t_handVector.z);
            Vector2 ghostVector = new(t_ghostVector.x, t_ghostVector.z);


            float angle = Vector2.Angle(handVector, ghostVector);
             
            if (!tsCustomApi.IsPlaying())
            {
                tsCustomApi.PlayAnimationAsset(TsCustomApi.AnimationAssetEnum.Pendant);
            }
            if (tsCustomApi.IsPlaying())
            {
                tsCustomApi.ChangeMultiplier(TsAPI.Types.TsHapticParamType.Amplitude, MapDistanceToIntensity(minDistance));
                tsCustomApi.ChangeMultiplier(TsAPI.Types.TsHapticParamType.Period, MapAngleToPeriod(angle));
            }
            


        }
    }

    private float MapDistanceToIntensity(float distance)
    {
        if (distance >= maxDistance)
        {
            return 0;
        }

        return  ( distance / maxDistance);

    }

    private float MapAngleToPeriod(float angle)
    {
        if (angle >= 180)
        {
            return 0;
        }

        return (angle / 180);

    }

    private void GetGhosts()
    {
        GameObject[] ghosts = GameObject.FindGameObjectsWithTag("Ghost");
        foreach (GameObject ghost in ghosts)
        {
            ghostList.Add(ghost);
        }
    }
}
