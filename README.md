# Library Management System

## Functional Requirements TODO

### A. Book Management Module

- [ ] 1. Add Book – Store book details (ISBN, title, author, genre, quantity).
- [ ] 2. Edit Book – Modify book information.
- [ ] 3. Delete Book – Remove a book from the system.
- [ ] 4. Search Book – Find a book by ISBN, title, or author.
- [ ] 5. List All Books – Display all available books.
- [x] 6. Store Book Records in a File – Save book data in binary/text format.
- [ ] 7. Load Book Records from File – Retrieve book data at startup.
- [ ] 8. Check Book Availability – Verify if a book is in stock.
- [ ] 9. Book Category Management – Organize books by genre (Fiction, Non-Fiction, etc.).
- [ ] 10. Book Status Tracking – Track if a book is available, borrowed, or lost.

### B. Member Management Module

- [x] 11. Add Member – Store member details (ID, name, contact, membership type).
- [ ] 12. Edit Member – Update member information.
- [ ] 13. Delete Member – Remove a member from the system.
- [ ] 14. Search Member – Find a member by ID, name, or contact.
- [ ] 15. List All Members – Display all registered members.
- [x] 16. Store Member Records in a File – Save member data persistently.
- [ ] 17. Load Member Records from File – Retrieve member data at startup.
- [ ] 18. Member Subscription Status – Track active/expired memberships.
- [ ] 19. Member Borrowing Limit – Enforce a max number of books per member.
- [ ] 20. Member Blacklist – Prevent loan access for defaulters.

### C. Loan & Reservation Module

- [ ] 21. Issue Loan – Assign a book to a member with a due date.
- [ ] 22. Return Book – Mark a book as returned.
- [ ] 23. Renew Loan – Extend the due date (if no reservations exist).
- [ ] 24. Check Overdue Loans – Identify late returns.
- [ ] 25. List All Active Loans – Display currently borrowed books.
- [ ] 26. Store Loan Records in a File – Save loan history.
- [ ] 27. Load Loan Records from File – Retrieve past loans.
- [ ] 28. Reserve Book – Allow members to reserve unavailable books.
- [ ] 29. Cancel Reservation – Remove a reservation entry.
- [ ] 30. Check Reservation Status – Notify when a reserved book is available.

### D. Fine & Payment Module

- [ ] 31. Calculate Fine – Apply charges for overdue books (e.g., $0.50/day).
- [ ] 32. Edit Fine – Adjust fine amount (waivers, discounts).
- [ ] 33. Delete Fine – Remove a fine record.
- [ ] 34. Search Fine – Find fines by member ID or book ISBN.
- [ ] 35. List All Fines – Display unpaid fines.
- [ ] 36. Store Fine Records in a File – Save financial data.
- [ ] 37. Load Fine Records from File – Retrieve fine history.
- [ ] 38. Process Payment – Mark fines as paid.
- [ ] 39. Partial Payment Support – Allow incremental payments.
- [ ] 40. Fine Exemption Rules – Waive fines for valid reasons (e.g., medical emergency).

### E. Reporting & Analytics Module

- [ ] 41. Book Popularity Report – Most borrowed books.
- [ ] 42. Member Activity Report – Frequent borrowers.
- [ ] 43. Revenue Report – Total fines collected.
- [ ] 44. Overdue Books Report – List all late returns.
- [ ] 45. Inventory Status Report – Books needing restocking.
- [ ] 46. Lost/Damaged Books Report – Track missing inventory.
- [ ] 47. Generate Monthly Summary – Loans, fines, new members.
- [ ] 48. Export Reports to File – Save reports in `.txt` or `.csv`.
- [ ] 49. Statistics Dashboard – Display key metrics (total books, active loans, etc.).
- [ ] 50. Audit Logging – Track system changes (who added/deleted books).

### F. Admin & Security Module

- [ ] 51. Admin Login System – Secure access with credentials.
- [ ] 52. Password Encryption – Store hashed passwords (basic implementation).
- [ ] 53. User Roles – Differentiate between librarians and members.
- [ ] 54. Activity Logs – Record admin actions (book edits, member deletions).
- [ ] 55. Backup & Restore – Save/load entire database from a backup file.