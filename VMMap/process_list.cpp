//------------------------------------------------------------------------------
// http://twpol.dyndns.org/projects/vmmap
// License: Microsoft Public License (Ms-PL).
//------------------------------------------------------------------------------

#include "StdAfx.h"
#include "process_list.h"

process_list::process_list(void)
{
	// Create process list for this user.
	// API: EnumProcesses: Windows 2000 Pro/Server.
	std::vector<DWORD> pids(1024);
	DWORD pids_needed = 0;
	if (!EnumProcesses(&*pids.begin(), pids.end() - pids.begin(), &pids_needed)) {
		std::tcerr << "EnumProcesses failed: " << std::hex << std::setw(8) << std::setfill(_T('0')) << GetLastError() << std::endl;
		return;
	}
	pids.resize(pids_needed / sizeof(DWORD));

	for (std::vector<DWORD>::iterator i = pids.begin(); i < pids.end(); i++) {
		process process(*i);
		//if ((process.image_filename().size() > 0) && (process.username().size() > 0)) {
			_processes.push_back(process);
		//}
	}
	_processes.sort(std::less<DWORD>());
}

process_list::~process_list(void)
{
}