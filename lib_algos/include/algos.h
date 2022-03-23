//
// Created by Saxion on 10/12/2018.
//

#ifndef ALGOS_ALGOS_H
#define ALGOS_ALGOS_H

#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include "task.h"

namespace saxion {
    struct algos {


        // 1 point
        template<typename _Iter>
        auto has_all_tasks_assigned(_Iter begin, _Iter end) const noexcept {
            // todo done (1)
            bool result = std::all_of(begin, end, []( const task i){
              return !i.assignees.empty(); });
            // returns true if all the tasks in collection have a person assigned to them
            return  result;
        }

        // 1 point
        template <typename _Iter>
        bool has_task_with_deadline_afer(_Iter begin, _Iter end, const task::time_type& deadline) const noexcept{
            // todo done (1)
          bool result = std::any_of(begin, end, [&deadline]( const task T) {
              return T.deadline > deadline;
          });
                // returns true if any of the tasks in collection have a deadline after <deadline>
            return result;
        }

        // 3 points
        template <typename _Iter>
        auto remove_asignee_from_all(_Iter begin, _Iter end, const std::string& person) const noexcept{
            // todo done (3)
            // This function transforms all the tasks in place by removing the specific 'person'.
            std::transform(begin, end, begin, [&person] (task& other_task) {
                // Here, you are trying to find your specific 'person':
                auto remove_person = std::find_if(other_task.assignees.begin(), other_task.assignees.end(), [&] (const std::string& name) {
                    return name == person; // Check if the person is equal.
                });

                // Check if the iterator of 'remove_person' is equal not equal to your end iterator.
                if (remove_person != other_task.assignees.end())
                    other_task.assignees.erase(remove_person); // Remove the person from the assignees.
                return other_task;
            });
        }

        // 1 point done
        template <typename _Iter>
        auto extend_deadlines(_Iter begin, _Iter end, int priority, const task::time_difference_type& extension) const noexcept{
            // todo done (1)

            // transforms the tasks with priority <prio> (in-place) by extending their deadlines with <extension>
            std::transform(begin, end, begin, [&extension, &priority]( task& T){
                if(T.priority == priority)
                (T.deadline += extension);
                return T ;});
        }

        // 1 point done
        template <typename _Iter>
        auto count_tasks_with_deadlines_before(_Iter begin, _Iter end, const task::time_type& deadline) const noexcept{
            // todo done (1)
            (void)begin; (void)end; (void)deadline;
            // returns the count of tasks with a deadline before <deadline>
            int count = std::count_if(begin, end,[&](task T){return  T.deadline < deadline;} );
            return count;
        }

        // 2 points
        template <typename _Iter>
        bool add_assignee_to_task(_Iter begin, _Iter end, int id, std::string person) const noexcept{
            // todo
            // adds <person> to assignees of the task with id <id>
            // returns false if such a task doesn't exist or if it already has <person> assigned to it
            // otherwise returns true
           // std::transform(begin, end, begin, [&](const task ))            return false;
            bool check = false;
            std::transform(begin, end, begin, [&](task T) {
                if (T.id == id) {
                    if(T.name.empty())
                        check = false;
                    T.name = std::move(person);
                }
                return T;
            });
            check = std::any_of(begin, end, [&](const task T) { return (T.name.compare(person)); });

            return  check;
        }

        // 1 point
        template <typename _Iter>
        std::vector<task> get_tasks_with_priority(_Iter begin, _Iter end, int priority) const noexcept{
            // todo done (1)
            std::vector<task> NewVec;
            (void)begin; (void)end; (void)priority;
            // returns a vector with copies of tasks with priority <priority>
            std::copy_if(begin, end, std::back_inserter(NewVec), [&](task T){return T.priority == priority;});
            return NewVec;
        }

        // 2 points move_if ;)
        template <typename _Iter, typename _OutIter>
        _Iter extract_tasks_with_deadline_before(_Iter begin, _Iter end,  _OutIter out, const task::time_type& deadline) const noexcept{
            // todo
            (void)begin; (void)end; (void)out; (void)deadline;
            // moves the tasks with deadlines before <deadline> to the container "pointed by" the <out> iterator (see test code for what it is)
            // the tasks that are on or after the <deadline> should stay in the *beginning* of the original container
            // the returned iterator should point to the 'new end' of the range in the original container

            /* Simplified example:
             * given an input container with integers: [6, 3, 7, 4, 5, 1]
             * move the numbers before number {5} to another container and return the new 'end' iterator to the original container.
             *
             * After moving numbers 'before {5}' the output container will have elements: [3, 4, 1],
             * while the original container will look like this: [6, 7, 5, _, _, _]
             * Notice that there are three empty slots at the end of the container and all the number >= 5 have been moved to the beginning.
             * The function should return the iterator to the 'new end' of the original container, which is the first empty slot.
             */
            return end;
        }

        using id_prio = std::tuple<int, int>;
        // 2 points
        template <typename _Iter>
        std::vector<id_prio> list_sorted_by_prio(_Iter begin, _Iter end) const noexcept{
            // todo done (1)
            (void)begin; (void)end;std::vector<id_prio> vector;

            // returns a vector of pairs <id, priority> of all the tasks. The returned vector must be sorted by priority.
            // If two tasks have the same priority, they are sorted by id (lower id comes first)
            std::sort(begin, end, [](const task T, const task J){
                if(T.priority != J.priority)
                return T.priority < J.priority;
                else
                   return T.id < J.id;
            });
            std::for_each(begin, end,[&vector](const task& T){vector.emplace_back(T.id, T.priority);});
           // std::move(begin, end, vector.cbegin(),[&vector](const task& T){vector.emplace_back(T.id, T.priority);});
            return vector;
        }

        // 1 point
        template <typename _Cont>
        auto remove_all_finished(_Cont& container) const noexcept{
            // todo
            (void)container;

            // removes all the tasks with deadline before or on the time point now() obtained from the system_clock
            // notice that this function takes the whole container as an argument, that's because it's impossible to remove elements using just the iterators.
        }


        // 1 point
        template <typename _Iter>
        task& get_nth_to_complete(_Iter begin, _Iter end, int n) const noexcept{
            // todo te doen
            (void)begin; (void)end; (void)n;
            // returns a reference to the n-th task to be completed in order of deadlines.
            // deadline ties are resolved by comparing priorities (lower priorities come first)
            _Iter found = std::find_if(begin, end, [&](task T){return T.priority < n;});
            return *found;
        }

        // 1 point
        template <typename _Iter>
        std::vector<task> get_first_n_to_complete(_Iter begin, _Iter end, int n) const noexcept{
            // todo te doen
            (void)begin; (void)end; (void)n;
            // returns a vector with copies of first n tasks to complete by deadline (ties resolved with priority).
            // The tasks in this vector must me sorted by deadline (ties resolved with priority)
            return std::vector<task>();
        }

        // 3 points
        template <typename _Iter, typename _OIter>
        void cost_burndown(_Iter begin, _Iter end, _OIter obegin) const noexcept {
            // todo
            (void)begin; (void)end; (void)obegin;
            // you can assume that _OIter is a std::back_insert_iterator to a container of double

            // calculates the cost burndown of the tasks and writes the output to the output iterator <obegin>
            // the cost burndown is defined as cumulative sum of the tasks' costs sorted by deadlines
            // tasks with the same deadline contribute one data point (sum of their costs) to the burndown

            /* Simplified example
             * Assume that we have a container with 5 tasks, where each task has a deadline and a cost associated with it:
             * [ {4, 43.0}, {2, 11.0}, {3, 7.0}, {1, 23.0}, {3, 19.0} ], here the first number in a pair is the deadline and the second the cost
             * The first task to complete is the 4th task (deadline 1) with associated cost of 23.0
             * The 2nd task to complete is the 2nd task (deadline 2) with associated cost of 11.0
             * The 3rd tasks to complete are the 3rd and the 5th tasks (deadline 3) with associated costs of 7.0 + 19.0 = 26.0
             * The 4th and last task to complete is the 1st task (deadline 4) with associated cost of 43.0
             *
             * Therefore the cost burndown (cumulative cost) is: [23.0, 34.0, 60.0, 103.0].
             * Those numbers in this order must be outputted to the obegin iterator.
             */
        }


        // 1 point
        template <typename _Iter>
        std::pair<task, task> cheapest_and_most_expensive(_Iter begin, _Iter end) const noexcept{
            // todo done (1)
           (void)begin; (void)end;

            // returns a pair consisting of the least and the most expensive tasks in the collection
           auto pair = std::minmax_element(begin, end,[](const task& T , const task& J){return T.cost < J.cost; });

            return  {*pair.first, *pair.second};;
        }

        // 1 point
        template <typename _Iter>
        auto total_cost(_Iter begin, _Iter end) const noexcept{
            // todo done (1)


         auto val =   std::accumulate(begin, end, 0.0, [](double cost, task T){return T.cost + cost;});

            return val;
        }

        // 2 points
        template <typename _Iter>
        double total_cost_of(_Iter begin, _Iter end, const std::string& assignee) const noexcept{
            // todo done (2)
            (void)begin; (void)end; (void)assignee;
            // returns the cost of all the tasks that have <assignee> assigned to them
          auto sum =  std::accumulate(begin, end, 0.0f, [&assignee](double cost, task T){if(T.assignees.find(assignee) != T.assignees.end()){return T.cost + cost;} else return cost;});
            return sum;
        }

        // 1 point
        template <typename _Iter>
        _Iter separate_by_deadline(_Iter begin, _Iter end, const task::time_type& deadline) const noexcept {
            // todo
            (void)begin; (void)end; (void)deadline;
            // reorders the tasks in such a way that all tasks with deadlines before <deadline> precede the tasks with deadline on or after <deadline>
            // returns the iterator to the last task in the first group (with deadlines before <deadline>)
            return begin;
        }

        // 3 points
        template <typename _Iter>
        double estimate_workload(_Iter begin, _Iter end, const std::string& person) const {
            // todo
            (void)begin; (void)end; (void)person;
            // estimates the workload of a <person>
            // the estimation is done as follows:
            // - out of all the tasks, half of them (n_s) are chosen at random (sampled)
            // - for the selected tasks a check is done, whether the <person> belongs to the task's assignees
            // based on the number of tasks that checked positive (count) and the total number of sampled tasks (n_s) the estimated workload is calculated as:
            // count / n_s

            /* Simplified example:
             * There are 8 tasks and "zack" is assigned to tasks [2, 3, 6].
             * We can construct a truth table of all tasks like this: [0, 0, 1, 1, 0, 0, 1, 0]
             * The true workload of "zack" is 3/8=0.375
             *
             * Let's say for the estimate we sampled tasks: 0, 2, 4, 6. For those sampled tasks "zack" is assigned 2 two times,
             * consequently the estimated workload is 2/4 = 0.5
             *
             * Let's now say that we randomly sampled tasks 1, 4, 6, 7. For those tasks "zack" appears only once,
             * therefore the estimated workload is 1/4 = 0.25
             *
             * Notice that for our example it is possible to estimate a workload between 0.00 & 0.75
             */

            return -1.0;
        }


        // 2 points
        template <typename _Iter>
        auto average_cost_of_prio(_Iter begin ,_Iter end, int priority) const noexcept{
            // todo done (2)
            (void)begin; (void)end; (void)priority;
            int count = 0;
           /* auto sum =  std::accumulate(begin, end, 0.0f, [&assignee](double cost, task T){
                if(T.assignees.find(assignee) != T.assignees.end()){return T.cost + cost;} else return cost;});
            return sum;*/
            // calculates and returns the average cost of tasks with priority <priority>
            double avg_cost = std::accumulate(begin, end,0.0, [&]( double cost,  task& T){
                if(priority == T.priority){
                    ++count;
                    return (T.cost + cost);
                }

               return cost;
            });

            return avg_cost/count;
        }
    };
}


#endif //ALGOS_ALGOS_H
