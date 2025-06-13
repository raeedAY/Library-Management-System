#ifndef MEMBER_MANAGEMENT_H
#define MEMBER_MANAGEMENT_H

#include "member.h"

#include <string>
#include <vector>

using namespace std;

void addMember(Member& member);
bool editMember(int memberId);
bool deleteMember(int memberId);
Member searchMember(int memberId);
vector<Member> listAllMembers();
bool updateMemberStatus(int memberId, bool isBlacklisted);
bool checkBorrowingLimit(int memberId);

    

#endif