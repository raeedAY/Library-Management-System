# Library Management System

## How to Build

```bash
g++ -std=c++20 -Iinclude src/main.cpp src/AdminSecurity/adminSecurity.cpp src/BookManagement/bookManagement.cpp src/FinePayment/finePayment.cpp src/LoanReservation/loanReservation.cpp src/MemberManagement/memberManagement.cpp src/ReportingAnalytics/reportingAnalytics.cpp src/UI/ui.cpp -o CppLMS.exe
```

## Functional Requirements TODO

### A. Book Management Module

- [x] 1. Add Book - Store book details (ISBN, title, author, genre, quantity).
- [x] 2. Edit Book – Modify book information.
- [x] 3. Delete Book – Remove a book from the system.
- [x] 4. Search Book – Find a book by ISBN, title, or author.
- [x] 5. List All Books – Display all available books.
- [x] 6. Store Book Records in a File – Save book data in binary/text format.
- [x] 7. Load Book Records from File – Retrieve book data at startup.
- [x] 8. Check Book Availability – Verify if a book is in stock.
- [ ] 9. Book Category Management – Organize books by genre (Fiction, Non-Fiction, etc.).
- [x] 10. Book Status Tracking – Track if a book is available, borrowed, or lost.

### B. Member Management Module

- [x] 11. Add Member – Store member details (ID, name, contact, membership type).
- [x] 12. Edit Member – Update member information.
- [x] 13. Delete Member – Remove a member from the system.
- [x] 14. Search Member – Find a member by ID, name, or contact.
- [x] 15. List All Members – Display all registered members.
- [x] 16. Store Member Records in a File – Save member data persistently.
- [x] 17. Load Member Records from File – Retrieve member data at startup.
- [x] 18. Member Subscription Status – Track active/expired memberships.
- [x] 19. Member Borrowing Limit – Enforce a max number of books per member.
- [x] 20. Member Blacklist – Prevent loan access for defaulters.

### C. Loan & Reservation Module

- [x] 21. Issue Loan – Assign a book to a member with a due date.
- [x] 22. Return Book – Mark a book as returned.
- [ ] 23. Renew Loan – Extend the due date (if no reservations exist).
- [x] 24. Check Overdue Loans – Identify late returns.
- [x] 25. List All Active Loans – Display currently borrowed books.
- [x] 26. Store Loan Records in a File – Save loan history.
- [x] 27. Load Loan Records from File – Retrieve past loans.
- [x] 28. Reserve Book – Allow members to reserve unavailable books.
- [x] 29. Cancel Reservation – Remove a reservation entry.
- [x] 30. Check Reservation Status – Notify when a reserved book is available.

### D. Fine & Payment Module

- [x] 31. Calculate Fine – Apply charges for overdue books (e.g., $0.50/day).
- [x] 32. Edit Fine – Adjust fine amount (waivers, discounts).
- [x] 33. Delete Fine – Remove a fine record.
- [x] 34. Search Fine – Find fines by member ID or book ISBN.
- [x] 35. List All Fines – Display unpaid fines.
- [x] 36. Store Fine Records in a File – Save financial data.
- [x] 37. Load Fine Records from File – Retrieve fine history.
- [x] 38. Process Payment – Mark fines as paid.
- [x] 39. Partial Payment Support – Allow incremental payments.
- [x] 40. Fine Exemption Rules – Waive fines for valid reasons (e.g., medical emergency).

### E. Reporting & Analytics Module

- [x] 41. Book Popularity Report – Most borrowed books.
- [x] 42. Member Activity Report – Frequent borrowers.
- [x] 43. Revenue Report – Total fines collected.
- [x] 44. Overdue Books Report – List all late returns.
- [ ] 45. Inventory Status Report – Books needing restocking.
- [ ] 46. Lost/Damaged Books Report – Track missing inventory.
- [ ] 47. Generate Monthly Summary – Loans, fines, new members.
- [ ] 48. Export Reports to File – Save reports in `.txt` or `.csv`.
- [x] 49. Statistics Dashboard – Display key metrics (total books, active loans, etc.).
- [x] 50. Audit Logging – Track system changes (who added/deleted books).

### F. Admin & Security Module

- [x] 51. Admin Login System – Secure access with credentials.
- [x] 52. Password Encryption – Store hashed passwords (basic implementation).
- [x] 53. User Roles – Differentiate between librarians and members.
- [x] 54. Activity Logs – Record admin actions (book edits, member deletions).
- [x] 55. Backup & Restore – Save/load entire database from a backup file.