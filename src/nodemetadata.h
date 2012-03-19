/*
Minetest-c55
Copyright (C) 2010-2011 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef NODEMETADATA_HEADER
#define NODEMETADATA_HEADER

#include "irrlichttypes.h"
#include <string>
#include <iostream>
#include <map>

/*
	NodeMetadata stores arbitary amounts of data for special blocks.
	Used for furnaces, chests and signs.

	There are two interaction methods: inventory menu and text input.
	Only one can be used for a single metadata, thus only inventory OR
	text input should exist in a metadata.
*/

class Inventory;
class IGameDef;

class NodeMetadata
{
public:
	NodeMetadata(IGameDef *gamedef);
	~NodeMetadata();
	
	void serialize(std::ostream &os) const;
	void deSerialize(std::istream &is);
	
	void clear();

	// Generic key/value store
	std::string getString(const std::string &name) const
	{
		std::map<std::string, std::string>::const_iterator i;
		i = m_stringvars.find(name);
		if(i == m_stringvars.end())
			return "";
		return i->second;
	}
	void setString(const std::string &name, const std::string &var)
	{
		if(var.empty())
			m_stringvars.erase(name);
		else
			m_stringvars[name] = var;
	}

	// The inventory
	Inventory* getInventory()
	{
		return m_inventory;
	}
	
	// If non-empty, player can interact by using an inventory view
	// See format in guiInventoryMenu.cpp.
	std::string getInventoryDrawSpec() const
	{
		return m_inventorydrawspec;
	}
	void setInventoryDrawSpec(const std::string &text)
	{
		m_inventorydrawspec = text;
	}
	
	// If non-empty, player can interact by using an form view
	// See format in guiFormMenu.cpp.
	std::string getFormSpec() const
	{
		return m_formspec;
	}
	void setFormSpec(const std::string &text)
	{
		m_formspec = text;
	}
	
	// Called on client-side; shown on screen when pointed at
	std::string getInfoText() const
	{
		return m_infotext;
	}
	void setInfoText(const std::string &text)
	{
		m_infotext = text;
	}
	
	// Whether the related node and this metadata can be removed
	bool getAllowRemoval() const
	{
		return m_allow_removal;
	}
	void setAllowRemoval(bool b)
	{
		m_allow_removal = b;
	}

private:
	std::map<std::string, std::string> m_stringvars;
	Inventory *m_inventory;
	std::string m_inventorydrawspec;
	std::string m_formspec;
	std::string m_infotext;
	bool m_allow_removal;
};


/*
	List of metadata of all the nodes of a block
*/

class NodeMetadataList
{
public:
	~NodeMetadataList();

	void serialize(std::ostream &os) const;
	void deSerialize(std::istream &is, IGameDef *gamedef);
	
	// Get pointer to data
	NodeMetadata* get(v3s16 p);
	// Deletes data
	void remove(v3s16 p);
	// Deletes old data and sets a new one
	void set(v3s16 p, NodeMetadata *d);
	// Deletes all
	void clear();
	
private:
	std::map<v3s16, NodeMetadata*> m_data;
};

#endif

