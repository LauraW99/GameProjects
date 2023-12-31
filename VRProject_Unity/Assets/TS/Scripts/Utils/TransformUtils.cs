using System;
using UnityEngine;

public static class TransformUtils
{
    public static Transform FindChildRecursive(Transform parent, string childName)
    {
        if (parent.name == childName)
        {
            return parent;
        }

        Transform result = null;

        foreach (Transform child in parent)
        {
            result = (child.name == childName) ? child.transform : FindChildRecursive(child, childName);
            if (result != null)
            {
                break;
            }
        }

        return result;
    }

    public static void IterateChildsRecursive(Transform parent, Func<Transform, bool> childFn)
    {
        if(childFn(parent))
        {
            return;
        }
        foreach (Transform child in parent)
        {
            IterateChildsRecursive(child, childFn);
        }
    }
}
