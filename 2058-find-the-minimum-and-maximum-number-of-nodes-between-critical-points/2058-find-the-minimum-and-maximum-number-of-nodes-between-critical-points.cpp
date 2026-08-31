class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prevCritical = -1;

        int minDist = INT_MAX;
        int maxDist = -1;

        int pos = 1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr != nullptr && curr->next != nullptr) {

            ListNode* next = curr->next;

            // Check if current node is a critical point
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                // First critical point
                if (first == -1) {
                    first = pos;
                }

                // If this is not the first critical point
                if (prevCritical != -1) {
                    minDist = min(minDist, pos - prevCritical);
                    maxDist = pos - first;
                }

                prevCritical = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        // Fewer than 2 critical points
        if (first == -1 || first == prevCritical) {
            return {-1, -1};
        }

        return {minDist, maxDist};
    }
};