/*
 * CRingBuffer.h
 *
 *  Created on: 07.05.2017
 *      Author: ben
 */

#ifndef CRINGBUFFER_H_
#define CRINGBUFFER_H_

class CRingBuffer
{
private:
	int32_t* 	m_pBuffer;
	uint32_t	m_nSize;
	uint32_t	m_cntFilled;
	uint32_t	m_idxWrite;
	uint32_t	m_idxRead;
public:
	int		CRingBuffer(uint32_t nSize);
	bool	put(uint32_t nData);
	bool	get(uint32_t &nData);
	void	print();
	void	clear();
	int 	~CRingBuffer();
};



#endif /* CRINGBUFFER_H_ */
