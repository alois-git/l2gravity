/*
 * CServerPacket.h - L2 GameServer Server Packet, threads FTW.
 * Created January 11, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifndef _ADENA_C_SERVER_PACKET_H_
#define _ADENA_C_SERVER_PACKET_H_

#include <CPacket.h>
#include <irrThread.h>
#include <IGameServerClient.h>
#include <CMemoryManager.h>

namespace adena
{
namespace game_server
{

	extern ADENALIB_API CMemoryManager ServerPacketMemoryManager;

	class CServerPacket : public CPacket
	{
	public:

		inline void* operator new ( size_t size )
		{
			return ServerPacketMemoryManager.allocate(size);
		};

		inline void operator delete( void* obj )
		{
			ServerPacketMemoryManager.deallocate(obj);
		};

		CServerPacket() : CPacket(), Writen(false) {}

		virtual ~CServerPacket() {}

		/*
		 * Any long tasks the the packet needs to do. Like sending other packets.
		 */
		virtual void run() {}

		virtual bool writePacket() = 0;

	protected:

		IGameServerClient* Client;
		bool Writen;

	};

}
}

#endif
