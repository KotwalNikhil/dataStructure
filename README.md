# DSA/ALGO Notes

## Goal
To maintain ideas/tricks and notes for dsa algo questions.

## Quick Index
* [Kadane Algo](#kadane-algo)

---

## 📚 Learning Resources
* [DSA crossiant resource](https://eminent-croissant-92f.notion.site/Resources-1e85855731e08102a565ce9ca22034e9) 

## Kadane Algo
- Each index will decide whether it will be a part of sub array or it will start a new subArray
  ### Maximum sum circular sub array
  - `ans = max(maxSubarraySum, totalSum-minSubarraySum)`
