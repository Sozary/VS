#include "ScriptHandle.h"

using namespace std;

ScriptHandle::ScriptHandle():m_content{MsgBox()}
{
}

void ScriptHandle::loadScript(Script script)
{
	// on parse vite fait le script

	for (int i = 0; i < script.instructions.size(); ++i)
	{
		if (script.instructions[i].script_type == "00")
			m_script_heap.identification = script.instructions[i];
		else if (script.instructions[i].script_type == "03")
			m_script_heap.aspect = script.instructions[i];
		else if (script.instructions[i].script_type == "04")
			m_script_heap.initial_raw_sequence = script.instructions[i];
		else
			m_script_heap.instruction_list.push_back(script.instructions[i]);
	}

}
void ScriptHandle::executeHeap(MsgBox& msgBox,bool* wait)
{	
	ifstream fichier("data/dialogues.dial", ios::in);
	//creer un objet msgBox
	vector<string> file;
	string tmp;
	while (getline(fichier, tmp))
		file.push_back(tmp);
	fichier.close();

	m_content.msgBox = msgBox;
	
	for (int i = 0; i < m_script_heap.instruction_list.size(); ++i)
	{
		if (m_script_heap.instruction_list[i].script_type == "01")//un dialogue
		{
			m_content.msgBox.addContent(file[hexToInt(m_script_heap.instruction_list[i].param)]);
			*wait = true;
			
		}
	}

	m_content.msgBox.setDrawable(true);
	
}
void ScriptHandle::next_action(bool* wait)
{
	
	m_content.msgBox.changeMsg();
	if (m_content.msgBox.isFinish())
		*wait = false;
}
ScriptHandle::~ScriptHandle()
{
}

int ScriptHandle::hexToInt(std::string str)
{
	int res;
	stringstream ss;
	ss << hex << str;
	ss >> res;
	return res;
}
