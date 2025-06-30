//
// Created by Andrei Luca on 29.06.2025.
//

#include "TemplateUtils.h"
#include <vector>
#include <limits>

int levenshteinDistance(const std::string& s1, const std::string& s2) {
    size_t n = s1.size(), m = s2.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1));
    for (size_t i=0; i<=n; ++i) dp[i][0] = i;
    for (size_t j=0; j<=m; ++j) dp[0][j] = j;
    for (size_t i=1; i<=n; ++i) {
        for (size_t j=1; j<=m; ++j) {
            int cost = (s1[i-1]==s2[j-1]? 0:1);
            dp[i][j] = std::min({ dp[i-1][j] + 1,
                                  dp[i][j-1] + 1,
                                  dp[i-1][j-1] + cost });
        }
    }
    return dp[n][m];
}
