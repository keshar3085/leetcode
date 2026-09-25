class Solution {
public:

    set<string> parse(string &s, int &i) {

        set<string> result;
        set<string> current;
        current.insert("");

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // OR: current result ko final result mein add karo
                result.insert(current.begin(), current.end());

                current.clear();
                current.insert("");

                i++;
            }
            else if (s[i] == '{') {

                i++; // skip '{'

                set<string> inside = parse(s, i);

                i++; // skip '}'

                // Concatenate current × inside
                set<string> next;

                for (string a : current) {
                    for (string b : inside) {
                        next.insert(a + b);
                    }
                }

                current = next;
            }
            else {
                // Normal character
                char c = s[i];

                set<string> next;

                for (string a : current) {
                    next.insert(a + c);
                }

                current = next;

                i++;
            }
        }

        // Add the last part
        result.insert(current.begin(), current.end());

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};