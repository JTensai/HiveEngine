#include "AIComponent.h"

using namespace Hive;

AIComponent::AIComponent()
{
}

void AIComponent::update_component(float delta)
{
	//TODO: update component

	Unit* player_unit = Unit::get_component(player_handle);
	glm::vec2 player_position = player_unit->get_position();
	Node goal(player_position.x, player_position.y);

	Unit* ai_unit = Unit::get_component(unit_handle);
	glm::vec2 ai_position = ai_unit->get_position();
	Node start(ai_position.x, ai_position.y);

	float dist_to_player = distance(player_position, ai_position);
	float player_position_delta = distance(player_position, cached_player_position);

	if (dist_to_player >= perception_exit_radius || dist_to_player < 0.5f)
	{
		glm::vec2 target(ai_unit->get_position());
		ai_unit->set_target(target);
		nav_path.clear();
		return;
	}

	if ((nav_path.size() == 0 || player_position_delta > 2.0f) && dist_to_player > 0.5 && dist_to_player <= perception_enter_radius)
	{
		cached_player_position = player_position;
		IGameWorld* game_world = ServiceLocator::get_game_world();
		pathfind_a_star(game_world->get_nav_mesh(), start, goal, EuclideanHeuristic(&goal));
		if (nav_path.size() > 0)
		{
			nav_path[nav_path.size() - 1]->set_width(player_position.x);
			nav_path[nav_path.size() - 1]->set_depth(player_position.y);

			glm::vec2 target(nav_path[0]->get_width() + 0.5, nav_path[0]->get_depth() + 0.5);
			ai_unit->set_target(target);
		}
		return;
	}

	if (nav_path.size() == 0)
	{
		return;
	}

	float dist_to_target = distance(ai_position, glm::vec2(nav_path[0]->get_width() + 0.5, nav_path[0]->get_depth() + 0.5));

	if (dist_to_target <= 0.25f)
	{
		nav_path.erase(nav_path.begin());

		if (nav_path.size() > 0)
		{
			glm::vec2 target(nav_path[0]->get_width() + 0.5, nav_path[0]->get_depth() + 0.5);
			ai_unit->set_target(target);
		}
	}
}

AIComponent::~AIComponent()
{
}

void AIComponent::pathfind_a_star(Graph* graph, Node& start, Node& end, BaseHeuristic& heuristic)
{
	PriorityQueue<NodeRecord> open(graph->get_map_width() * graph->get_map_depth());
	vector<NodeRecord> closed;//list of visited nodes

	NodeRecord start_record;
	start_record.node = &start;
	start_record.node->set_parent(nullptr);
	start_record.cost_so_far = 0;
	start_record.estimated_total_cost = heuristic.estimate(&start);

	open.insert(start_record);

	while (open.size() > 0)
	{
		NodeRecord curr = open.deleteMin();
		closed.push_back(curr);

		if (*curr.node == end)
		{
			generate_path(curr.node, &start);
			closed.clear();
			return;
		}

		vector<Node*> connecting_nodes = *graph->get_connections(curr.node);

		for (int i = 0; i < connecting_nodes.size(); ++i)
		{
			if (contains(open, connecting_nodes[i]))
			{
				NodeRecord temp = find(open, connecting_nodes[i]);
				float temp_cost = curr.cost_so_far + curr.node->distance_to(connecting_nodes[i]);
				if (temp.cost_so_far > temp_cost)
				{
					open.delete_object(temp);

					//temp.fromNode = &curr;
					temp.node->set_parent(curr.node);
					temp.cost_so_far = temp_cost;
					temp.estimated_total_cost = temp.cost_so_far + heuristic.estimate(curr.node);

					open.insert(temp);
				}
			}
			else if (contains(closed, connecting_nodes[i]))
			{
				NodeRecord temp = find(closed, connecting_nodes[i]);
				float temp_cost = curr.cost_so_far + curr.node->distance_to(connecting_nodes[i]);
				if (temp.cost_so_far > temp_cost)
				{
					remove(closed, temp);

					//temp.fromNode = &curr;
					temp.node->set_parent(curr.node);
					temp.cost_so_far = temp_cost;
					temp.estimated_total_cost = temp.cost_so_far + heuristic.estimate(curr.node);

					closed.push_back(temp);
				}
			}
			else
			{
				NodeRecord to_add;
				to_add.node = connecting_nodes[i];
				//toAdd.fromNode = &curr;
				to_add.node->set_parent(curr.node);
				to_add.cost_so_far = curr.cost_so_far + curr.node->distance_to(to_add.node);
				to_add.estimated_total_cost = to_add.cost_so_far + heuristic.estimate(to_add.node);

				open.insert(to_add);
			}
		}
	}
	//return &vector<Node*>();
}

void AIComponent::generate_path(Node* curr, Node* start)
{
	nav_path.clear();
	nav_path.insert(nav_path.begin(), curr);

	while (curr->get_parent() != nullptr)
	{
		Node* temp = curr;
		curr = curr->get_parent();
		temp->set_parent(nullptr);
		nav_path.insert(nav_path.begin(), curr);
	}
	smooth_path();
	nav_path.erase(nav_path.begin());
}

bool AIComponent::contains(PriorityQueue<NodeRecord>& pq, Node* node)
{
	int size = pq.size();
	for (int i = 0; i < size; ++i)
	{
		if (*node == *pq.get_index(i).node)
		{
			return true;
		}
	}
	return false;
}

bool AIComponent::contains(vector<NodeRecord>& closed, Node* node)
{
	int size = (int)closed.size();
	for (int i = 0; i < size; ++i)
	{
		if (*node == *closed[i].node)
		{
			return true;
		}
	}
	return false;
}

AIComponent::NodeRecord AIComponent::find(PriorityQueue<NodeRecord>& pq, Node* toFind)
{
	NodeRecord toReturn;
	int size = pq.size();
	for (int i = 0; i < size; ++i)
	{
		NodeRecord temp = pq.get_index(i);
		if (*toFind == *temp.node)
		{
			toReturn = temp;
			break;
		}
	}
	return toReturn;
}

AIComponent::NodeRecord AIComponent::find(vector<NodeRecord>& closed, Node* toFind)
{
	NodeRecord toReturn;
	int size = (int)closed.size();
	for (int i = 0; i < size; ++i)
	{
		NodeRecord temp = closed[i];
		if (*toFind == *temp.node)
		{
			toReturn = temp;
			break;
		}
	}
	return toReturn;
}

void AIComponent::remove(vector<NodeRecord>& closed, NodeRecord toRemove)
{
	for (int i = 0; i < closed.size(); ++i)
	{
		if (toRemove == closed[i])
		{
			closed.erase(closed.begin() + i);
			break;
		}
	}
}

void AIComponent::set_unit_handle(int unit_handle)
{
	this->unit_handle = unit_handle;
}

void AIComponent::set_player_handle(int player_handle)
{
	this->player_handle = player_handle;
}

float AIComponent::distance(glm::vec2 a, glm::vec2 b)
{
	float diff_x = a.x - b.x;
	float diff_y = a.y - b.y;
	return sqrt((diff_x * diff_x) + (diff_y * diff_y));
}

void AIComponent::smooth_path()
{
	// if the path is only 2 or fewer nodes long, then we can't smooth it, so return
	if (nav_path.size() <= 2)
	{
		return;
	}

	vector<Node*> smoothedPath;
	smoothedPath.push_back(nav_path[0]);

	// keep track of where we are in the input path
	// start at 2, because we assume 2 adjacent nodes will pass the ray cast
	int inputIndex = 2;

	// loop until we find the last item in the input
	while (inputIndex < nav_path.size() - 1)
	{
		// do the ray cast
		if (!ray_clear(smoothedPath[smoothedPath.size() - 1], nav_path[inputIndex]))
		{
			// the ray test failed, add the last node that passed to the smoothedPath
			smoothedPath.push_back(nav_path[inputIndex - 1]);
		}

		//consider the next node
		++inputIndex;
	}

	// we've reached the end of the input path, add the end node to the smoothedPath
	smoothedPath.push_back(nav_path[nav_path.size() - 1]);

	// update the nav_path to be the new smoothedPath
	nav_path.clear();
	nav_path = smoothedPath;
}

bool AIComponent::ray_clear(Node* start, Node* end)
{
	IGameWorld* game_world = ServiceLocator::get_game_world();
	vector<char> grid = game_world->grid();

	int diff_x = end->get_width() - start->get_width();
	int diff_y = end->get_depth() - start->get_depth();
	float slope = diff_x == 0 ? std::numeric_limits<float>::infinity() : diff_y / diff_x;

	if (start->get_width() == end->get_width()) // are they in the same column
	{
		int depth_index = start->get_depth();
		do
		{
			// iterate by decrementing
			if (start->get_depth() > end->get_depth()) { --depth_index; }
			// iterate by incrementing
			else { ++depth_index; }

			if (grid[(depth_index * game_world->width()) + start->get_width()] != '\x1') { return false; }

		} while (depth_index != end->get_depth());
		return true;
	}
	else if (start->get_depth() == end->get_depth()) // are they in the same row
	{
		int width_index = start->get_width();
		do
		{
			// iterate by decrementing
			if (start->get_width() > end->get_width()) { --width_index; }
			// iterate by incrementing
			else { ++width_index; }

			if (grid[(start->get_depth() * game_world->width()) + width_index] != '\x1') { return false; }

		} while (width_index != end->get_width());
		return true;
	}
	else if (slope == 1 || slope == -1) // are they diagonal
	{
		int width_index = start->get_width();
		int depth_index = start->get_depth();
		do
		{
			// iterate by decrementing
			if (start->get_depth() > end->get_depth()) { --depth_index; }
			// iterate by incrementing
			else { ++depth_index; }

			// iterate width by decrementing
			if (start->get_width() > end->get_width()) { --width_index; }
			// iterate width by incrementing
			else { ++width_index; }

			if (grid[(depth_index * game_world->width()) + width_index] != '\x1') { return false; }

		} while (depth_index != end->get_depth());
		return true;
	}

	const float offset = 0.2f;

	//tan(@) = opposite / adjacent
	//@ = atan2(opposite/adjacent)
	float angle = abs(atan2(diff_y, diff_x));// 0 <= angle <= PI
	//angle = angle > PI / 2 ? PI - angle : angle;
	const float x_offset = diff_x > 0 ? cos(angle) * offset : cos(angle) * offset * -1;// adjacent = cos(@) * hypotenuse
	const float y_offset = diff_y > 0 ? sin(angle) * offset : sin(angle) * offset * -1;// opposite = sin(@) * hypotenuse

	//float normalize_diff_x = float(diff_x) / float(abs(diff_y));
	//float normalize_diff_y = diff_y > 0 ? 1 : -1; // = diff_y / diff_y
	float curr_x = start->get_width() - 0.5;
	float curr_y = start->get_depth() - 0.5;
	int curr_width = curr_x;
	int curr_depth = curr_y;

	do
	{
		curr_x += x_offset;
		curr_y += y_offset;
		curr_width = int(curr_x);
		curr_depth = int(curr_y);

		if (grid[(curr_depth * game_world->width()) + curr_width] != '\x1') { return false; }

	} while (curr_width != end->get_width() && curr_depth != end->get_depth());
	return true;
}

void AIComponent::set_perception_enter_radius(float enter_radius)
{
	perception_enter_radius = enter_radius;
}

void AIComponent::set_perception_exit_radius(float exit_radius)
{
	perception_exit_radius = exit_radius;
}