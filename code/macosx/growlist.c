#include "../splines/q_shared.h"

extern void *Com_Allocate( int bytes );
extern void Com_Dealloc( void *ptr );

void Com_InitGrowList( growList_t *list, int maxElements ) {
	list->maxElements = maxElements;
	list->currentElements = 0;
	list->elements = (void **)Com_Allocate( list->maxElements * sizeof( void * ) );
}

int Com_AddToGrowList( growList_t *list, void *data ) {
	void	**old;

	if ( list->currentElements != list->maxElements ) {
		list->elements[list->currentElements] = data;
		return list->currentElements++;
	}

	old = list->elements;

	if ( list->maxElements < 0 ) {
		Com_Error( ERR_FATAL, "Com_AddToGrowList: maxElements = %i", list->maxElements );
	}

	if ( list->maxElements == 0 ) {
		Com_InitGrowList( list, 100 );
		return Com_AddToGrowList( list, data );
	}

	list->maxElements *= 2;

	Com_DPrintf( "Resizing growlist to %i maxElements\n", list->maxElements );

	list->elements = (void **)Com_Allocate( list->maxElements * sizeof( void * ) );

	if ( !list->elements ) {
		Com_Error( ERR_DROP, "Growlist alloc failed" );
	}

	memcpy( list->elements, old, list->currentElements * sizeof( void * ) );

	Com_Dealloc( old );

	return Com_AddToGrowList( list, data );
}

void *Com_GrowListElement( const growList_t *list, int index ) {
	if ( index < 0 || index >= list->currentElements ) {
		Com_Error( ERR_DROP, "Com_GrowListElement: %i out of range of %i", 
			index, list->currentElements );
	}
	return list->elements[index];
}

int Com_IndexForGrowListElement( const growList_t *list, const void *element ) {
	int		i;

	for ( i = 0 ; i < list->currentElements ; i++ ) {
		if ( list->elements[i] == element ) {
			return i;
		}
	}
	return -1;
}
