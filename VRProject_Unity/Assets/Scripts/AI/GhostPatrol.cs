using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class GhostPatrol : MonoBehaviour
{
    public Transform[] points;
    private int current;
    public float speed;
    public float distanceThreshold = 0.1f;
    public LayerMask obstacleLayer; 
    private Transform player;
    private NavMeshAgent enemy;
    private bool hasLineOfSight = false;
    private Vector3 lastPlayerPosition;

    void Start()
    {
        current = 0;
        player = GameObject.FindGameObjectWithTag("Player").transform;
        enemy = GetComponent<NavMeshAgent>();
        enemy.SetDestination(points[current].position);
    }

    void Update()
    {
        float distanceToPlayer = Vector3.Distance(transform.position, player.position);

        hasLineOfSight = HasLineOfSightToPlayer();

        if (hasLineOfSight)
        {
            lastPlayerPosition = player.position;
            enemy.SetDestination(lastPlayerPosition);
        }
        else
        {
            if (Vector3.Equals(enemy.transform.position, lastPlayerPosition))
            {
                enemy.SetDestination(lastPlayerPosition);
            }
            
            else
            {
                float remainingDistance = enemy.remainingDistance;
                if (remainingDistance < distanceThreshold)
            {
                current = (current + 1) % points.Length;
                enemy.SetDestination(points[current].position);
            }
            }
        }
    }

    private bool HasLineOfSightToPlayer()
    {
        RaycastHit hit;

        Vector3 directionToPlayer = player.position - transform.position;

        bool lineOfSight = Physics.Raycast(
            transform.position,
            directionToPlayer.normalized, 
            out hit,
            Mathf.Infinity,
            obstacleLayer
        );

        Debug.DrawRay(transform.position, directionToPlayer.normalized * hit.distance, Color.red);

        return lineOfSight && hit.collider.gameObject.layer == LayerMask.NameToLayer("Player");
    }
}
