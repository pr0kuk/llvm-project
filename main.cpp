#pragma once
#define HEIGHT 1000
#define WIDTH 1000
#include <iostream>
#include <vector>
#include "point.hpp"
#include "vordiag.hpp"
#include <utility>

int divide(Vordiag vect, Vordiag& l_vect, Vordiag& r_vect)
{
    return 0;
}

std::pair<std::pair<int,int>, std::pair<int,int>> upper_bound(Vordiag l_vect, Vordiag r_vect) {
    return std::make_pair(std::make_pair(-1,-1), std::make_pair(-1,-1));
}

std::pair<std::pair<int,int>, std::pair<int,int>> serp(std::pair<std::pair<int,int>, std::pair<int,int>> otr) {
    return std::make_pair(std::make_pair(-1,-1), std::make_pair(-1,-1));
}


std::pair<int, int> percline(std::pair<std::pair<int,int>, std::pair<int,int>> line1, std::pair<std::pair<int,int>, std::pair<int,int>> line2)
{
    if ((line1.second.first-line1.first.first)*(line2.second.second-line2.first.second)-(line1.second.second-line1.first.second)*(line2.second.first-line2.first.first) != 0) {
        return std::make_pair(-1, -1);
    }
    else {
        return std::make_pair(-1, -1);
    }
}

std::pair<int, int> perc(std::pair<std::pair<int,int>, std::pair<int,int>> srp, Vordiag vordiag, std::pair<int, int>& smezh_point)
{
    int n = vordiag.vorline.size();
    std::pair<int, int> ret;
    std::pair<int, int> check = std::make_pair(-1, -1);
    for (int i = 0; i < n; i++) {
        ret = percline(srp, vordiag.vorline[i].line);
        if (ret != check)
            break;
    }
    return ret;
}


Vordiag merge(Vordiag l_vect, Vordiag r_vect)
{
    std::pair<int, int> per, perl, perr, check = std::make_pair(-1, -1);
    std::pair<std::pair<int,int>, std::pair<int,int>> srp, otr;
    otr = upper_bound(l_vect, r_vect);
    std::pair<int, int> smezh_point = check;
    while(1) {
        srp = serp(otr);
        perl = perc(srp, l_vect, smezh_point);
        perr =  perc(srp, r_vect, smezh_point);
        if (perl == check && perr == check)
            break;
        if (perl < perr) {
            per = perl;
            //otr.first = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
        }
        else {
            per = perr;
            //otr.second = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
        }
    }
    Vordiag m_vect = l_vect; // !!!!!!!!!!!!!!!!!!!!!
    return m_vect;
}


Vordiag iter(Vordiag vect)
{
    Vordiag l_vect, r_vect;
    divide(vect, l_vect, r_vect);
    if (l_vect.vorline.size() > 1)
        iter(l_vect);
    if (r_vect.vorline.size() > 1)
        iter(r_vect);
    Vordiag m_vect = merge(l_vect, r_vect);
    return m_vect;
}




int main()
{
    std::vector<Point> points(16);
    return 0;
}