#pragma once
#include <cstdint>

#include "engine_data.h"

class base_object
{
public:
	base_object() = default;

	base_object(vertex* const vertices, uint32_t* const indices);

	base_object(vertex* const vertices, uint32_t const vertex_count, uint32_t* const indices, const mat_4& world_matrix);

	~base_object();

	base_object(const base_object& other) = default;

	base_object(base_object&& other) noexcept;

	base_object& operator=(const base_object& other);

	base_object& operator=(base_object&& other) noexcept;

	friend bool operator==(const base_object& lhs, const base_object& rhs);

	friend bool operator!=(const base_object& lhs, const base_object& rhs);

	friend bool operator<(const base_object& lhs, const base_object& rhs);

	friend bool operator<=(const base_object& lhs, const base_object& rhs);

	friend bool operator>(const base_object& lhs, const base_object& rhs);

	friend bool operator>=(const base_object& lhs, const base_object& rhs);

	vertex* get_vertices() const;

	void set_vertices(vertex* const vertices);

	uint32_t get_vertex_count() const;

	void set_vertex_count(const uint32_t vertex_count);

	uint32_t* get_indices() const;

	void set_indices(uint32_t* const indices);

	mat_4 get_world_matrix() const;

	void set_world_matrix(const mat_4& world_matrix);

private:
	vertex* vertices_ = nullptr;
	uint32_t vertex_count_{};
	uint32_t* indices_ = nullptr;

	base_object* parent_ = nullptr;

	mat_4 world_matrix_ = mat_4::identity();
	mat_4 relative_matrix_ = mat_4::identity();
};
