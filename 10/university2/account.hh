/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * A new account includes an account number, name, contact info, total credits
 * and a boolean value determining whether this account has graduated.
 *
 * An account has a vector<Course*> containing all courses that this account
 * has ever signed up for and another vector<bool> with corresponding
 * boolean values (false if the is passed, true otherwise).
 *
 * Class Account has methods, which are implemented calling other functions
 * from class Course, and methods in this class are then called in
 * class University.
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";
using vector_size_type = std::vector<int>::size_type;

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief is_graduated
     * @return bool value if the account has graduated or not
     */
    bool is_graduated();

    /**
     * @brief signs up the given student for the given course.
     * @param course code
     */
    void sign_up_course( Course* &code );

    /**
     * @brief complete_course
     * @param course code
     * The course is completed, then bool value enrolled turns false
     * If course is already completed or isn't signed up, error is given
     */
    void complete_course( Course* &code );

    /**
     * @brief is_current_course
     * @param course code
     * @return true if still enroll in this course, otherwise, false
     */
    bool is_current_course( const std::string &code );

    /**
     * @brief is_completed_course
     * @param code
     * @return true if course is completed, otherwise, false
     */
    bool is_completed_course ( const std::string &code );

    /**
     * @brief is_signed_up_course
     * @param code
     * @return true is course is in attribute course_ vector
     * This method is then used for printing signups in University class
     */
    bool is_signed_up_course ( const std::string &code );

    /**
     * @brief print_study_state
     * include current and completed course, credits
     */
    void print_study_state();

    /**
     * @brief print_completed_courses
     */
    void print_completed();

    /**
     * @brief graduate
     * This account graduate and can no longer sign up for any course
     */
    void graduate();


private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    // courses the account has signed up for
    // completed and uncompleted
    std::vector<Course*> courses_;

    // boolean vector: true if uncompleted (still enrolled in class)
    // false if completed
    std::vector<bool> currently_enrolled_;
    int total_credits_; // credits from completed course
    bool graduated_;    // graduated means completed all courses
};

#endif // ACCOUNT_HH


