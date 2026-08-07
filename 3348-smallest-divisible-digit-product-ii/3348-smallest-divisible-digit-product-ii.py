from collections import deque

class Solution(object):
    def smallestNumber(self, num, t):
        """
        :type num: str
        :type t: int
        :rtype: str

        Returns the smallest zero-free number >= num whose digit-product
        is divisible by t, or "-1" if none exists.
        """

        # Edge case: if t == 1, any product is divisible by 1, so just fix zero digits in num if any:
        if t == 1:
            return self._nextZeroFreeAtLeast(num)

        # Factorize t. If prime factors outside {2,3,5,7} appear, no solution.
        a, b, c, d = self._factorize_2_3_5_7(t)
        if a < 0:
            return "-1"

        # Build BFS/DP table for minimal number of digits to achieve coverage
        # of at least 2^x * 3^y * 5^z * 7^w (x<=a,y<=b,z<=c,w<=d).
        cost_table = self._build_min_digit_cost(a, b, c, d)
        if cost_table[a][b][c][d] == float('inf'):
            return "-1"

        # Try same length first
        L = len(num)
        ans_same = self._buildNextBiggerOrEqual(num, a, b, c, d, cost_table)
        if ans_same is not None:
            return ans_same

        # If same-length fails, try bigger lengths
        needed_min = cost_table[a][b][c][d]
        # We try lengths from L+1 up to L+needed_min+1, in ascending order
        # The first feasible we find is the lexicographically smallest.
        for extra_len in range(1, needed_min + 2):
            length_candidate = L + extra_len
            ans_bigger = self._buildSmallest(length_candidate, a, b, c, d, cost_table)
            if ans_bigger is not None:
                return ans_bigger

        return "-1"

    # -------------------------------------------------------
    #  1) Convert s => next zero-free >= s
    # -------------------------------------------------------
    def _nextZeroFreeAtLeast(self, s):
        """
        Returns the smallest zero-free integer as a string, >= s.
        If s is already zero-free, returns s.
        Otherwise, correct digits from left to right.
        """
        digits = list(map(int, s))
        n = len(digits)
        # Quick check if already zero-free
        if all(d != 0 for d in digits):
            return s

        i = 0
        while i < n:
            if digits[i] == 0:
                # Need to carry up from i
                j = i
                while j >= 0 and digits[j] == 9:
                    j -= 1
                if j < 0:
                    # All were 9 up to i => we must prepend '1' and set rest to '1'
                    return '1' + ('1'*n)
                digits[j] += 1
                # set all from j+1 ... end to '1'
                for k in range(j+1, n):
                    digits[k] = 1
                break
            i += 1

        # final pass: if any 0 remains, set to 1
        for idx in range(n):
            if digits[idx] == 0:
                digits[idx] = 1
        return "".join(map(str, digits))

    # -------------------------------------------------------
    #  2) Factor t into (a,b,c,d) where t = 2^a * 3^b * 5^c * 7^d
    # -------------------------------------------------------
    def _factorize_2_3_5_7(self, t):
        a = b = c = d = 0
        for prime in [2, 3, 5, 7]:
            while t % prime == 0:
                if prime == 2: a += 1
                elif prime == 3: b += 1
                elif prime == 5: c += 1
                elif prime == 7: d += 1
                t //= prime
        if t > 1:
            # leftover prime factor outside {2,3,5,7}
            return -1, -1, -1, -1
        return a, b, c, d

    # -------------------------------------------------------
    #  3) BFS to build cost_table[x][y][z][w] = minimal # digits
    #     to get coverage >= x,y,z,w from digits [1..9].
    # -------------------------------------------------------
    def _build_min_digit_cost(self, maxA, maxB, maxC, maxD):
        INF = float('inf')
        cost = [[[[INF]*(maxD+1) for _ in range(maxC+1)]
                 for _ in range(maxB+1)]
                for _ in range(maxA+1)]

        # Map digit -> factor increments
        digit_factors = {
            1: (0,0,0,0),
            2: (1,0,0,0),
            3: (0,1,0,0),
            4: (2,0,0,0),
            5: (0,0,1,0),
            6: (1,1,0,0),
            7: (0,0,0,1),
            8: (3,0,0,0),
            9: (0,2,0,0),
        }

        from collections import deque
        q = deque()
        cost[0][0][0][0] = 0
        q.append((0,0,0,0))

        while q:
            x, y, z, w = q.popleft()
            base_cost = cost[x][y][z][w]
            for dgt in range(1, 10):
                dx, dy, dz, dw = digit_factors[dgt]
                # new coverage is min(x+dx, maxA), etc.
                nx = min(x+dx, maxA)
                ny = min(y+dy, maxB)
                nz = min(z+dz, maxC)
                nw = min(w+dw, maxD)
                if cost[nx][ny][nz][nw] == INF:
                    cost[nx][ny][nz][nw] = base_cost + 1
                    q.append((nx, ny, nz, nw))
        return cost

    # -------------------------------------------------------
    #  4) Build the smallest zero-free number of length=length_target
    #     that has coverage >= (a,b,c,d).
    # -------------------------------------------------------
    def _buildSmallest(self, length_target, a, b, c, d, cost_table):
        INF = float('inf')
        res = []
        A, B, C, D = a, b, c, d
        for i in range(length_target):
            placed_digit = None
            for dgt in range(1, 10):
                na, nb, nc, nd = self._subFactor(A,B,C,D,dgt)  # <-- CLAMPS leftover to >=0
                # check if feasible
                # i.e. can the leftover be covered in the remaining (length_target - i - 1) digits?
                if cost_table[na][nb][nc][nd] <= (length_target - i - 1):
                    placed_digit = dgt
                    A, B, C, D = na, nb, nc, nd
                    break
            if placed_digit is None:
                return None
            res.append(str(placed_digit))

        # At the end, leftover must be fully covered => cost_table[A][B][C][D] == 0
        if cost_table[A][B][C][D] != 0:
            return None

        return "".join(res)

    # -------------------------------------------------------
    #  5) Build next bigger/equal of same length as num
    #     that has coverage >= (a,b,c,d).
    # -------------------------------------------------------
    def _buildNextBiggerOrEqual(self, num, a, b, c, d, cost_table):
        digits = list(map(int, num))
        L = len(digits)
        ans = [0]*L

        def backtrack(pos, is_equal, A, B, C, D):
            if pos == L:
                # must have leftover coverage done
                return (cost_table[A][B][C][D] == 0)

            start_dig = digits[pos] if is_equal else 1
            for dgt in range(start_dig, 10):
                if dgt == 0:
                    continue  # skip zero
                na, nb, nc, nd = self._subFactor(A,B,C,D,dgt)  # clamp leftover
                # check feasibility with remaining digits
                if cost_table[na][nb][nc][nd] <= (L - pos - 1):
                    ans[pos] = dgt
                    if backtrack(pos+1,
                                 is_equal and (dgt == start_dig),
                                 na, nb, nc, nd):
                        return True
            return False

        ok = backtrack(0, True, a, b, c, d)
        if not ok:
            return None
        return "".join(map(str, ans))

    # -------------------------------------------------------
    #  6) Helper: subtract digit's prime factors, clamp to zero.
    # -------------------------------------------------------
    def _subFactor(self, A, B, C, D, digit):
        """
        Subtract the digit's prime factors from leftover coverage, 
        but clamp to 0 if it goes negative (over-coverage is allowed).
        """
        if digit == 1:
            fa, fb, fc, fd = 0, 0, 0, 0
        elif digit == 2:
            fa, fb, fc, fd = 1, 0, 0, 0
        elif digit == 3:
            fa, fb, fc, fd = 0, 1, 0, 0
        elif digit == 4:
            fa, fb, fc, fd = 2, 0, 0, 0
        elif digit == 5:
            fa, fb, fc, fd = 0, 0, 1, 0
        elif digit == 6:
            fa, fb, fc, fd = 1, 1, 0, 0
        elif digit == 7:
            fa, fb, fc, fd = 0, 0, 0, 1
        elif digit == 8:
            fa, fb, fc, fd = 3, 0, 0, 0
        else:  # digit == 9
            fa, fb, fc, fd = 0, 2, 0, 0

        return (max(A - fa, 0),
                max(B - fb, 0),
                max(C - fc, 0),
                max(D - fd, 0))

#
# If you want to do a quick test:
#
if __name__ == "__main__":
    sol = Solution()

    # Provided example that was failing:
    print(sol.smallestNumber("12355", 50))  
    # Expected => "12355"
    # Over-coverage fix yields "12355" now.