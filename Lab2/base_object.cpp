#include "base_object.h"

#include <utility>

#include "engine_data.h"

base_object::base_object(vertex* const vertices, uint32_t* const indices)
	: vertices_(vertices),
	  vertex_count_(0),
	  indices_(indices), parent_(nullptr),
	  world_matrix_(mat_4(vec4::zero(), vec4::zero(), vec4::zero(), {0, 0, 0, 1}))
{
}

base_object::base_object(vertex* const vertices, uint32_t const vertex_count, uint32_t* const indices,
                         const mat_4& world_matrix): vertices_(vertices),
                                                     vertex_count_(vertex_count),
                                                     indices_(indices), parent_(nullptr),
                                                     world_matrix_(world_matrix)
{
}

base_object::~base_object()
{
	delete[] vertices_;
	delete[] indices_;
}

base_object::base_object(base_object&& other) noexcept: vertices_(other.vertices_),
                                                        vertex_count_(other.vertex_count_),
                                                        indices_(other.indices_), parent_(nullptr),
                                                        world_matrix_(other.world_matrix_)
{
}

base_object& base_object::operator=(const base_object& other)
{
	if (this == &other)
		return *this;
	vertices_ = other.vertices_;
	vertex_count_ = other.vertex_count_;
	indices_ = other.indices_;
	world_matrix_ = other.world_matrix_;
	return *this;
}

base_object& base_object::operator=(base_object&& other) noexcept
{
	if (this == &other)
		return *this;
	vertices_ = other.vertices_;
	vertex_count_ = other.vertex_count_;
	indices_ = other.indices_;
	world_matrix_ = std::move(other.world_matrix_);
	return *this;
}

vertex* base_object::get_vertices() const
{
	return vertices_;
}

void base_object::set_vertices(vertex* const vertices)
{
	vertices_ = vertices;
}

uint32_t base_object::get_vertex_count() const
{
	return vertex_count_;
}

void base_object::set_vertex_count(const uint32_t vertex_count)
{
	vertex_count_ = vertex_count;
}

uint32_t* base_object::get_indices() const
{
	return indices_;
}

void base_object::set_indices(uint32_t* const indices)
{
	indices_ = indices;
}

mat_4 base_object::get_world_matrix() const
{
	return world_matrix_;
}

void base_object::set_world_matrix(const mat_4& world_matrix)
{
	this->world_matrix_ = world_matrix;
}

bool operator==(const base_object& lhs, const base_object& rhs)
{
	return lhs.vertices_ == rhs.vertices_
		&& lhs.vertex_count_ == rhs.vertex_count_
		&& lhs.indices_ == rhs.indices_
		&& lhs.world_matrix_ == rhs.world_matrix_;
}

bool operator!=(const base_object& lhs, const base_object& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const base_object& lhs, const base_object& rhs)
{
	if (lhs.vertices_ < rhs.vertices_)
		return true;
	if (rhs.vertices_ < lhs.vertices_)
		return false;
	if (lhs.vertex_count_ < rhs.vertex_count_)
		return true;
	if (rhs.vertex_count_ < lhs.vertex_count_)
		return false;
	if (lhs.indices_ < rhs.indices_)
		return true;
	if (rhs.indices_ < lhs.indices_)
		return false;
	return lhs.world_matrix_ < rhs.world_matrix_;
}

bool operator<=(const base_object& lhs, const base_object& rhs)
{
	return !(rhs < lhs);
}

bool operator>(const base_object& lhs, const base_object& rhs)
{
	return rhs < lhs;
}

bool operator>=(const base_object& lhs, const base_object& rhs)
{
	return !(lhs < rhs);
}
